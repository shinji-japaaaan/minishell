/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:11:06 by karai             #+#    #+#             */
/*   Updated: 2025/02/08 21:27:34 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	return (*list_head);
}

void	expand_env_variables_in_list(t_linked_list *list_head, int last_status, char **env)
{
	t_linked_list	*ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		ptr_temp->content = expansion(ptr_temp->content, last_status, env);
		ptr_temp = ptr_temp->next;
	}
}

t_cmd_invoke	*parser(char *input, int last_status, char **env)
{
	t_linked_list	*head;
	t_cmd_invoke	*cmd_head;

	head = linked_list_init(NULL);
	if (head == NULL)
	{
		ft_putendl_fd("Failed to initialize linked list.", 2);
		return (NULL);
	}
	tokenize_input(head, input);
	assign_token_types(head);
	expand_env_variables_in_list(head, last_status, env);
	remove_quotes_from_tokens(head);
	if (parse_error_last_token(head) || parse_error_consecutive_pipe(head)
		|| parse_error_consecutive_redirect(head))
	{
		ft_putendl_fd("syntax error", 2);
		free_linked_list_only_node(&head);
		return (NULL);
	}
	cmd_head = cmd_invoke_init(NULL);
	cmd_head = make_cmd(head, cmd_head);
	free_linked_list_only_node(&head);
	return (cmd_head);
}
