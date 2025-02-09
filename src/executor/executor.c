/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:25:07 by karai             #+#    #+#             */
/*   Updated: 2025/02/09 09:59:06 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parent_process_wait(t_cmd_invoke *head)
{
	int				status;
	t_cmd_invoke	*temp_ptr;
	int				ret_status;

	temp_ptr = head->next;
	while (temp_ptr)
	{
		waitpid(temp_ptr->pid, &status, 0);
		heredoc_close(temp_ptr);
		temp_ptr = temp_ptr->next;
	}
	if (WIFSIGNALED(status))
	{
		ret_status = (WTERMSIG(status)) + 128;
		if (ret_status == 130)
			write(1, "\n", 1);
		else if (ret_status == 131)
			ft_putendl_fd("Quit (core dumped)", 1);
		return (ret_status);
	}
	return (WEXITSTATUS(status));
}

void	close_fd_in_child(t_cmd_invoke *node)
{
	t_redirect	*redirect_head;
	t_redirect	*temp_ptr;

	redirect_head = node->redirect_head;
	temp_ptr = redirect_head->next;
	while (temp_ptr)
	{
		close(temp_ptr->stdio_backup);
		temp_ptr = temp_ptr->next;
	}
}

void	handle_command_execution(t_cmd_invoke *temp_ptr, bool is_first)
{
	if (is_first)
	{
		if (temp_ptr->next != NULL)
			cmd_execute_first(temp_ptr);
	}
	else
	{
		if (temp_ptr->next == NULL)
			cmd_execute_last(temp_ptr);
		else
			cmd_execute_middle(temp_ptr);
	}
}

void	handle_open_redirect(t_cmd_invoke *head, t_cmd_invoke *temp_ptr)
{
	int	status;

	status = open_redirect(temp_ptr, false);
	if (status != 0)
	{
		close_fd_in_child(temp_ptr);
		free_all(&head);
		exit(status);
	}
}

void	process_cmd_invoke(t_cmd_invoke *temp_ptr, char **env) // 関数名を変更
{
	char *path;

	path = get_path_main(temp_ptr, env); // 修正: t_cmd_invoke 型を渡す
	execve(path, temp_ptr->cmd_list, env);
}

void	cmd_execute_child(t_cmd_invoke *head, t_cmd_invoke *temp_ptr,
		bool is_first, char **env)
{
	handle_command_execution(temp_ptr, is_first);
	handle_open_redirect(head, temp_ptr);
	if (!is_internal_commands(temp_ptr->cmd_list[0]))
		process_cmd_invoke(temp_ptr, env); // 新しい関数名を呼び出す
	else
		exit(handle_internal_commands(temp_ptr, &env));
}

void	cmd_execute_parent(t_cmd_invoke *temp_ptr, bool *is_first)
{
	if (*is_first == false)
	{
		close(temp_ptr->bef_pipefd[0]);
		close(temp_ptr->bef_pipefd[1]);
	}
	heredoc_close(temp_ptr);
	*is_first = false;
}

int	cmd_execute_main(t_cmd_invoke *head, char **env, int *last_status)
{
	t_cmd_invoke	*temp_ptr;
	bool			is_first;

	heredoc_main(head, env, last_status);
	if (g_signal == SIGINT)
		return (*last_status);
	is_first = true;
	temp_ptr = head->next;
	set_sig_during_exec();
	while (temp_ptr)
	{
		if (temp_ptr->next != NULL)
		{
			pipe(temp_ptr->nxt_pipefd);
			temp_ptr->next->bef_pipefd = temp_ptr->nxt_pipefd;
		}
		temp_ptr->pid = fork();
		if (temp_ptr->pid == 0)
		{
			set_sig_handler_child();
			cmd_execute_child(head, temp_ptr, is_first, env);
		}
		cmd_execute_parent(temp_ptr, &is_first);
		temp_ptr = temp_ptr->next;
	}
	return (parent_process_wait(head));
}
