/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:11:06 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 17:58:42 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_linked_list	*remove_quotes_tokens(t_linked_list *list_head)
{
	t_linked_list	*ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		if (ptr_temp->token_type == TYPE_COMMAND)
		{
			if (ptr_temp->content != NULL)
			{
				ptr_temp->content = remove_quote(ptr_temp->content, ptr_temp);
				if (ptr_temp->content == NULL)
					return (free_linked_list_all(&list_head), NULL);
			}
		}
		ptr_temp = ptr_temp->next;
	}
	return (list_head);
}

t_linked_list	*expand_env_var_in_list(t_linked_list *list_head,
		int last_status, char **env)
{
	t_linked_list	*ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		ptr_temp->content = expansion(ptr_temp->content, last_status, env);
		if (ptr_temp->content == NULL)
			return (free_linked_list_all(&list_head), NULL);
		ptr_temp = ptr_temp->next;
	}
	return (list_head);
}

void	change_emp_to_null(t_linked_list *list_head)
{
	t_linked_list	*ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		if (ptr_temp->content[0] == '\0')
		{
			free(ptr_temp->content);
			ptr_temp->content = NULL;
		}
		ptr_temp = ptr_temp->next;
	}
}

t_linked_list	*parse_for_ll(t_linked_list *head, char *input, int last_status,
		char **env)
{
	if (tokenize_input(head, input) == NULL)
		return (ft_putendl_fd("Failed to tokenize.", 2), NULL);
	assign_token_types(head);
	if (expand_env_var_in_list(head, last_status, env) == NULL)
		return (ft_putendl_fd("Failed to expansion.", 2), NULL);
	change_emp_to_null(head);
	if (remove_quotes_tokens(head) == NULL)
		return (ft_putendl_fd("Failed to remove quotes.", 2), NULL);
	return (head);
}

t_cmd_invoke	*parser(char *input, int last_status, char **env)
{
	t_linked_list	*head;
	t_cmd_invoke	*cmd_head;

	head = linked_list_init(NULL);
	if (head == NULL)
		return (ft_putendl_fd("Failed to initialize linked list.", 2), NULL);
	if (parse_for_ll(head, input, last_status, env) == NULL)
		return (NULL);
	if (parse_error_last_token(head) || parse_error_consecutive_pipe(head)
		|| parse_error_consec_red(head))
	{
		ft_putendl_fd("syntax error", 2);
		return (free_linked_list_only_node(&head), NULL);
	}
	cmd_head = cmd_invoke_init(NULL);
	if (cmd_head == NULL)
		return (ft_putendl_fd("Failed to initialize cmd list.", 2), NULL);
	cmd_head = make_cmd(head, cmd_head);
	if (cmd_head == NULL)
		return (ft_putendl_fd("Failed to make cmd.", 2), NULL);
	free_linked_list_only_node(&head);
	return (cmd_head);
}
