/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:18:22 by karai             #+#    #+#             */
/*   Updated: 2025/01/13 20:30:27 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "parser.h"

TokenType	get_token_type(char *str)
{
	if (strcmp(str, "|") == 0)
		return (TYPE_PIPE);
	if (strcmp(str, "<") == 0)
		return (TYPE_REDIRECT_IN);
	if (strcmp(str, ">") == 0)
		return (TYPE_REDIRECT_OUT);
	if (strcmp(str, "<<") == 0)
		return (TYPE_HEREDOC);
	if (strcmp(str, ">>") == 0)
		return (TYPE_REDIRECT_APPEND);
	return (TYPE_COMMAND);
}

void	linked_list_tokenize(t_linked_list *list_head)
{
	t_linked_list *ptr_temp;

	ptr_temp = list_head->next;
	while(ptr_temp)
	{
		ptr_temp->token_type = get_token_type(ptr_temp->content);
		ptr_temp = ptr_temp->next;
	}
}
