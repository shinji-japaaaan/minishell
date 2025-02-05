/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:27:30 by karai             #+#    #+#             */
/*   Updated: 2025/01/31 23:29:23 by karai            ###   ########.fr       */
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

void	free_cmd_node(t_cmd_invoke *node)
{
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

void	free_linked_list_only_node(t_linked_list **head_list)
{
	t_linked_list	*nxt_ptr;
	t_linked_list	*now_ptr;

	now_ptr = *head_list;
	while (now_ptr)
	{
		nxt_ptr = now_ptr->next;
		free(now_ptr);
		now_ptr = nxt_ptr;
	}
	*head_list = NULL;
}

void	free_linked_list_all(t_linked_list **head_list)
{
	t_linked_list	*nxt_ptr;
	t_linked_list	*now_ptr;

	now_ptr = *head_list;
	while (now_ptr)
	{
		nxt_ptr = now_ptr->next;
		free(now_ptr->content);
		free(now_ptr);
		now_ptr = nxt_ptr;
	}
	*head_list = NULL;
}
