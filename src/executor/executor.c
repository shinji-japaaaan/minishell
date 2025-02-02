/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:25:07 by karai             #+#    #+#             */
/*   Updated: 2025/02/02 08:11:12 by karai            ###   ########.fr       */
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
		heredoc_close(temp_ptr);
		temp_ptr = temp_ptr->next;
	}
	if (WIFSIGNALED(status))
		return (status + 128);
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

void	cmd_execute_child(t_cmd_invoke *head, t_cmd_invoke *temp_ptr,
		bool is_first, int interrupted)
{
	int			status;
	extern char	**environ;
	char		*path;

	if (interrupted)
	{
		heredoc_close(temp_ptr);
		free_all(&head);
		exit(130);
	}
	if (is_first && temp_ptr->next != NULL)
		cmd_execute_first(temp_ptr);
	else if (!is_first && temp_ptr->next == NULL)
		cmd_execute_last(temp_ptr);
	else if (!is_first && temp_ptr->next != NULL)
		cmd_execute_middle(temp_ptr);
	status = open_redirect(temp_ptr, false);
	if (status != 0)
	{
		close_fd_in_child(temp_ptr);
		free_all(&head);
		exit(status);
	}
	if (!is_internal_commands(temp_ptr->cmd_list[0]))
	{
		path = get_path_main(temp_ptr);
		execve(path, temp_ptr->cmd_list, environ);
	}
	else
		exit(handle_internal_commands(temp_ptr, environ));
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

int	cmd_execute_main(t_cmd_invoke *head)
{
	t_cmd_invoke	*temp_ptr;
	bool			is_first;
	int				interrupted;

	is_first = true;
	temp_ptr = head->next;
	while (temp_ptr)
	{
		if (temp_ptr->next != NULL)
		{
			pipe(temp_ptr->nxt_pipefd);
			temp_ptr->next->bef_pipefd = temp_ptr->nxt_pipefd;
		}
		interrupted = heredoc_redirect_list(temp_ptr->redirect_head);
		temp_ptr->pid = fork();
		if (temp_ptr->pid != 0)
			global_pid = temp_ptr->pid;
		if (temp_ptr->pid == 0)
			cmd_execute_child(head, temp_ptr, is_first, interrupted);
		cmd_execute_parent(temp_ptr, &is_first);
		temp_ptr = temp_ptr->next;
	}
	return (parent_process_wait(head));
}
