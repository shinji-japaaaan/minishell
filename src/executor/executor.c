/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:25:07 by karai             #+#    #+#             */
/*   Updated: 2025/01/19 07:27:37 by sishizaw         ###   ########.fr       */
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
	// if (waitpid(pid[0], &status, 0) == -1)
	// {
	// 	// later
	// 	// perror_exit("wait failed", NULL, NULL, 1);
	// }
}

void	cmd_execute_first_last(t_cmd_invoke *node)
{
	char		*path;
	extern char	**environ;

	path = get_path_main(node);
	execve(path, node->cmd_list, environ);
}

void	cmd_execute_first(t_cmd_invoke *node)
{
	char		*path;
	extern char	**environ;

	dup2(node->nxt_pipefd[1], 1);
	close(node->nxt_pipefd[0]);
	close(node->nxt_pipefd[1]);
	path = get_path_main(node);
	execve(path, node->cmd_list, environ);
}

void	cmd_execute_last(t_cmd_invoke *node)
{
	char		*path;
	extern char	**environ;

	dup2(node->bef_pipefd[0], 0);
	close(node->bef_pipefd[0]);
	close(node->bef_pipefd[1]);
	path = get_path_main(node);
	execve(path, node->cmd_list, environ);
}

void	cmd_execute_middle(t_cmd_invoke *node)
{
	char		*path;
	extern char	**environ;

	dup2(node->bef_pipefd[0], 0);
	dup2(node->nxt_pipefd[1], 1);
	close(node->bef_pipefd[0]);
	close(node->bef_pipefd[1]);
	close(node->nxt_pipefd[0]);
	close(node->nxt_pipefd[1]);
	path = get_path_main(node);
	execve(path, node->cmd_list, environ);
}

int	cmd_execute_main(t_cmd_invoke *head)
{
	t_cmd_invoke	*temp_ptr;
	int				status;
	bool			is_first;

	is_first = true;
	temp_ptr = head->next;
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
			if (is_first && temp_ptr->next == NULL)
			{
				cmd_execute_first_last(temp_ptr);
			}
			else if (is_first)
			{
				cmd_execute_first(temp_ptr);
			}
			else if (temp_ptr->next == NULL)
			{
				cmd_execute_last(temp_ptr);
			}
			else
				cmd_execute_middle(temp_ptr);
		}
		else
		{
			if (is_first == false)
			{
				close(temp_ptr->bef_pipefd[0]);
				close(temp_ptr->bef_pipefd[1]);
			}
		}
		is_first = false;
		temp_ptr = temp_ptr->next;
	}
	status = parent_process_wait(head);
	return (status);
}
