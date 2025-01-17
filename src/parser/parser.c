/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:11:06 by karai             #+#    #+#             */
/*   Updated: 2025/01/17 22:25:29 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_linked_list	remove_quotes_from_tokens(t_linked_list *list_head)
{
	t_linked_list	*ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		if (ptr_temp->token_type == TYPE_COMMAND)
		{
			ptr_temp->content = remove_quote(ptr_temp->content);
		}
		ptr_temp = ptr_temp->next;
	}
	return *list_head;  // list_headの値を返す
}

void	expand_env_variables_in_list(t_linked_list *list_head)
{
	t_linked_list	*ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		ptr_temp->content = expansion(ptr_temp->content);
		ptr_temp = ptr_temp->next;
	}
}

t_linked_list *parser(char *input)
{
    t_linked_list *head;

	head = NULL;
    head = linked_list_init(head);
    tokenize_input(head, input); // トークン化処理を呼び出し
    assign_token_types(head);
    expand_env_variables_in_list(head);
    remove_quotes_from_tokens(head);
    return (head);
}
