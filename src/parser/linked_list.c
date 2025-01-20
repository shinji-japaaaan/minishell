/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:10:28 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/20 21:29:43 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// for test
void	linked_list_print(t_linked_list *list_head)
{
	t_linked_list	*ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		printf("%s\n", ptr_temp->content);
		ptr_temp = ptr_temp->next;
	}
}

// for test
void	linked_list_print_with_token(t_linked_list *list_head)
{
	t_linked_list *ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		printf("token type: %d\n", ptr_temp->token_type);
		printf("%s\n", ptr_temp->content);
		ptr_temp = ptr_temp->next;
	}
}

void	linked_list_free(t_cmd_invoke *list_head)
{
	t_cmd_invoke *temp;
	t_cmd_invoke *current;

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
	t_linked_list *new_node;

	new_node = NULL;
    new_node = linked_list_init(new_node);
	new_node->content = strdup(str);
	free(str);
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

t_linked_list	*linked_list_init(t_linked_list *new_node)
{
	new_node = (t_linked_list *)malloc(sizeof(t_linked_list));
	new_node->content = NULL;
	new_node->next = NULL;
	new_node->token_type = TYPE_DEFAULT;
	return (new_node);
}
