/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:20:24 by karai             #+#    #+#             */
/*   Updated: 2025/01/12 16:40:03 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "parser.h"

t_linked_list	*linked_list_init(t_linked_list *new_node)
{
	new_node = (t_linked_list *)malloc(sizeof(t_linked_list));
	new_node->content = NULL;
	new_node->next = NULL;
	new_node->type = 0;
	return (new_node);
}

void	linked_list_append(t_linked_list *list_head, char *str)
{
	t_linked_list	*new_node;
	t_linked_list	*ptr_temp;

	new_node = linked_list_init(new_node);
	new_node->content = strdup(str);
	if (list_head->next == NULL)
	{
		list_head->next = new_node;
	}
	else
	{
		ptr_temp = list_head;
		while (ptr_temp->next != NULL)
		{
			ptr_temp = ptr_temp->next;
		}
		ptr_temp->next = new_node;
	}
}

void	linked_list_print(t_linked_list *list_head)
{
	t_linked_list *ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		printf("%s\n", ptr_temp->content);
		ptr_temp = ptr_temp->next;
	}
}
