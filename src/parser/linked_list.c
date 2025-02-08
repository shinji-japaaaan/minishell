/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:10:28 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/08 22:38:47 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	linked_list_free(t_cmd_invoke *list_head)
{
	t_cmd_invoke	*temp;
	t_cmd_invoke	*current;

	current = list_head;
	while (current != NULL)
	{
		temp = current->next;
		if (current->cmd_list)
			free(current->cmd_list);
		free(current);
		current = temp;
	}
}

void	linked_list_append(t_linked_list *list_head, char *str)
{
	t_linked_list	*ptr_temp;
	t_linked_list	*new_node;
	
	new_node = linked_list_init(NULL);
	new_node->content = ft_strdup(str);
	free(str);
	if (list_head->next == NULL)
		list_head->next = new_node;
	else
	{
		ptr_temp = list_head;
		while (ptr_temp->next != NULL)
			ptr_temp = ptr_temp->next;
		ptr_temp->next = new_node;
	}
}

t_linked_list	*linked_list_init(t_linked_list *new_node)
{
	new_node = (t_linked_list *)malloc(sizeof(t_linked_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = NULL;
	new_node->next = NULL;
	new_node->token_type = TYPE_DEFAULT;
	return (new_node);
}