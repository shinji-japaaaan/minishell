/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:10:28 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/18 14:11:53 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

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

void	linked_list_free(t_linked_list *list_head)
{
	t_linked_list *temp;
	t_linked_list *current;

	current = list_head;
	while (current != NULL)
	{
		temp = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = temp;
	}
}

void	linked_list_append(t_linked_list *list_head, char *str)
{
	t_linked_list	*ptr_temp;
	t_linked_list *new_node = NULL;
    new_node = linked_list_init(new_node);
	new_node->content = strdup(str);
	//list_head->contentがNULLの場合、最初のノードにデータを格納
    if (list_head->content == NULL)
    {
        list_head->content = new_node->content;
    }
    else if (list_head->next == NULL) // 次のノードが無ければ、リストの末尾に追加
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