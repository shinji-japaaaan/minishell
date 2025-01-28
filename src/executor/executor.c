/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:25:07 by karai             #+#    #+#             */
/*   Updated: 2025/01/28 22:15:18 by karai            ###   ########.fr       */
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
		reset_redirect(temp_ptr, false);
		temp_ptr = temp_ptr->next;
	}
	if (WIFSIGNALED(status))
		return (WIFSIGNALED(status));
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
			// ft_putendl_fd("1\n", 2);
			if (is_first && temp_ptr->next != NULL)
				cmd_execute_first(temp_ptr); //  pipe connect
			else if (!is_first && temp_ptr->next == NULL)
				cmd_execute_last(temp_ptr); //  pipe connect
			else if (!is_first && temp_ptr->next != NULL)
				cmd_execute_middle(temp_ptr); //  pipe connect
			status = open_redirect(temp_ptr); // processing redirect
			if (status != 0)
			{
				close_fd_in_child(temp_ptr);
				// free_cmd_node(temp_ptr);
				free_all(&head);
				exit(status);
			}
			if (!is_internal_commands(temp_ptr->cmd_list[0]))
			{
				path = get_path_main(temp_ptr);            //  get command path
				execve(path, temp_ptr->cmd_list, environ); // execute command
			}
			else
				exit(handle_internal_commands(temp_ptr, environ));
		}
		if (is_first == false)
		{
			close(temp_ptr->bef_pipefd[0]);
			close(temp_ptr->bef_pipefd[1]);
		}
		// ft_putendl_fd("3\n", 2);
		is_first = false;
		temp_ptr = temp_ptr->next; // move to next command
	}
	status = parent_process_wait(head);
	// wait for finishing child process in parent process
	return (status);
}
