/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:25:07 by karai             #+#    #+#             */
/*   Updated: 2025/01/24 21:16:55 by karai            ###   ########.fr       */
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
	if (WIFSIGNALED(status))
		return (WIFSIGNALED(status));
	return (WEXITSTATUS(status));
}

void	cmd_execute_first(t_cmd_invoke *node)
{
	dup2(node->nxt_pipefd[1], 1);
	close(node->nxt_pipefd[0]);
	close(node->nxt_pipefd[1]);
}

void	cmd_execute_last(t_cmd_invoke *node)
{
	dup2(node->bef_pipefd[0], 0);
	close(node->bef_pipefd[0]);
	close(node->bef_pipefd[1]);
}

void	cmd_execute_middle(t_cmd_invoke *node)
{
	dup2(node->bef_pipefd[0], 0);
	dup2(node->nxt_pipefd[1], 1);
	close(node->bef_pipefd[0]);
	close(node->bef_pipefd[1]);
	close(node->nxt_pipefd[0]);
	close(node->nxt_pipefd[1]);
}

int	cmd_execute_main(t_cmd_invoke *head)
{
	t_cmd_invoke	*temp_ptr;
	int				status;
	bool			is_first;
	char			*path;
	extern char		**environ;
	int				status_handle_internal_command;

	is_first = true;
	temp_ptr = head->next;
	while (temp_ptr)
	{
		if (temp_ptr->next != NULL)
		{
			pipe(temp_ptr->nxt_pipefd); // create pipe
			temp_ptr->next->bef_pipefd = temp_ptr->nxt_pipefd;
			// pipe connect to next command
		}
		temp_ptr->pid = fork();
		if (temp_ptr->pid == 0) // start child process
		{
			if (is_first)
				cmd_execute_first(temp_ptr); //  pipe connect
			else if (temp_ptr->next == NULL)
				cmd_execute_last(temp_ptr); //  pipe connect
			else if (!is_first && temp_ptr->next != NULL)
				cmd_execute_middle(temp_ptr); //  pipe connect
			open_redirect(temp_ptr);          // processing redirect
			status_handle_internal_command = handle_internal_commands(temp_ptr->cmd_list[0],
					temp_ptr->cmd_list[1], environ);
			if (!status_handle_internal_command)
			{
				path = get_path_main(temp_ptr);            //  get command path
				execve(path, temp_ptr->cmd_list, environ); // execute command
			}
			else
				exit (status_handle_internal_command);
		}
		else // start parent process
		{
			if (is_first == false)
			{
				close(temp_ptr->bef_pipefd[0]);
				// close not using pipe connection
				close(temp_ptr->bef_pipefd[1]);
				// close not using pipe connection
			}
		}
		is_first = false;
		reset_redirect(temp_ptr);  // redirect shall be reset for next command.
		temp_ptr = temp_ptr->next; // move to next command
	}
	status = parent_process_wait(head);
	// wait for finishing child process in parent process
	return (status);
}
