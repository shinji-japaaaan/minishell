/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:25:07 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 18:21:52 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parent_process_wait(t_cmd_invoke *head)
{
	int				status;
	t_cmd_invoke	*temp_ptr;

	temp_ptr = head->next;
	while (temp_ptr)
	{
		waitpid(temp_ptr->pid, &status, 0);
		temp_ptr = temp_ptr->next;
	}
	temp_ptr = head->next;
	while (temp_ptr)
	{
		heredoc_close(temp_ptr);
		temp_ptr = temp_ptr->next;
	}
	if (WIFSIGNALED(status))
	{
		status = (WTERMSIG(status)) + 128;
		if (status == 130)
			write(1, "\n", 1);
		else if (status == 131)
			ft_putendl_fd("Quit (core dumped)", 2);
		return (status);
	}
	return (WEXITSTATUS(status));
}

void	process_cmd_invoke(t_cmd_invoke *temp_ptr, char **env,
		t_cmd_invoke *head)
{
	char	*path;

	if (temp_ptr->cmd_list[0][0] == '\0')
	{
		ft_putendl_fd("'' command not found", 2);
		fext_incmdpath(NULL, head, env, NON_COMMAND);
	}
	path = get_path_main(temp_ptr, env, head);
	execve(path, temp_ptr->cmd_list, env);
}

void	cmd_execute_child(t_cmd_invoke *head, t_cmd_invoke *temp_ptr,
		bool is_first, char **env)
{
	int	status;

	handle_command_execution(temp_ptr, is_first);
	handle_open_redirect(head, temp_ptr, env);
	if (temp_ptr->cmd_list[0] == NULL)
	{
		free_all(&head);
		free_env(env);
		exit(0);
	}
	if (!is_internal_commands(temp_ptr->cmd_list[0]))
		process_cmd_invoke(temp_ptr, env, head);
	else
	{
		status = handle_internal_commands(temp_ptr, &env);
		free_all(&head);
		free_env(env);
		exit(status);
	}
}

t_cmd_invoke	*cmd_execute_parent(t_cmd_invoke *temp_ptr, bool *is_first)
{
	if (*is_first == false)
	{
		close(temp_ptr->bef_pipefd[0]);
		close(temp_ptr->bef_pipefd[1]);
	}
	heredoc_close(temp_ptr);
	*is_first = false;
	return (temp_ptr->next);
}

int	cmd_execute_main(t_cmd_invoke *head, char **env, int *last_status,
		t_History *history)
{
	t_cmd_invoke	*temp_ptr;
	bool			is_first;

	heredoc_main(head, env, last_status);
	if (g_signal == SIGINT)
		return (*last_status);
	set_sig_during_exec();
	is_first = true;
	temp_ptr = head->next;
	while (temp_ptr)
	{
		if (temp_ptr->next != NULL)
			if (cmd_pipe_connect(temp_ptr) == NULL)
				break ;
		temp_ptr->pid = fork();
		if (temp_ptr->pid == 0)
		{
			free_history(history);
			heredoc_close_nu(head, temp_ptr);
			set_sig_handler_child();
			cmd_execute_child(head, temp_ptr, is_first, env);
		}
		temp_ptr = cmd_execute_parent(temp_ptr, &is_first);
	}
	return (parent_process_wait(head));
}
