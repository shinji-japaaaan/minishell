/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:27:30 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 09:49:00 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_redirect(t_redirect **redirect_head)
{
	t_redirect	*nxt_ptr;
	t_redirect	*now_ptr;

	now_ptr = *redirect_head;
	while (now_ptr)
	{
		nxt_ptr = now_ptr->next;
		free(now_ptr->filename);
		free(now_ptr);
		now_ptr = nxt_ptr;
	}
	*redirect_head = NULL;
}

void	close_fd_in_child(t_cmd_invoke *node)
{
	t_redirect	*redirect_head;
	t_redirect	*temp_ptr;
	struct stat	st;

	redirect_head = node->redirect_head;
	temp_ptr = redirect_head->next;
	while (temp_ptr)
	{
		if (fstat(temp_ptr->stdio_backup, &st) == 0)
		{
			close(temp_ptr->stdio_backup);
		}
		temp_ptr = temp_ptr->next;
	}
}

void	free_cmd_node(t_cmd_invoke *node)
{
	close_fd_in_child(node);
	free_redirect(&(node->redirect_head));
	free2dim(&(node->cmd_list));
	free(node);
}

void	free_all(t_cmd_invoke **cmd_head)
{
	t_cmd_invoke	*nxt_ptr;
	t_cmd_invoke	*now_ptr;

	now_ptr = *cmd_head;
	while (now_ptr)
	{
		nxt_ptr = now_ptr->next;
		free_cmd_node(now_ptr);
		now_ptr = nxt_ptr;
	}
	*cmd_head = NULL;
}

void	fext_incmdpath(char **dir_array, t_cmd_invoke *head, char **env,
		int exit_status)
{
	(void)head;
	free2dim(&dir_array);
	free_all(&head);
	free_env(env);
	exit(exit_status);
}
