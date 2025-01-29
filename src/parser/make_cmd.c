/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:29:31 by karai             #+#    #+#             */
/*   Updated: 2025/01/29 22:08:26 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_cmd_len_list(t_cmd_invoke *head)
{
	size_t			i;
	t_cmd_invoke	*temp_ptr;

	i = 0;
	temp_ptr = head->next;
	while (temp_ptr)
	{
		i += 1;
		temp_ptr = temp_ptr->next;
	}
	return (i);
}

t_redirect	*redirect_init(t_redirect *new_node)
{
	new_node = (t_redirect *)malloc(sizeof(t_redirect));
	new_node->filename = NULL;
	new_node->token_type = TYPE_DEFAULT;
	new_node->next = NULL;
	return (new_node);
}

t_cmd_invoke	*cmd_invoke_init(t_cmd_invoke *new_node)
{
	new_node = (t_cmd_invoke *)malloc(sizeof(t_cmd_invoke));
	new_node->cmd_list = NULL;
	new_node->redirect_head = NULL;
	new_node->redirect_head = redirect_init(new_node->redirect_head);
	new_node->next = NULL;
	return (new_node);
}

size_t	ft_cmd_len(t_linked_list *node)
{
	size_t	cmd_len;
	bool	is_filename;

	cmd_len = 0;
	is_filename = false;
	while (node != NULL && node->token_type != TYPE_PIPE)
	{
		if (is_filename)
			is_filename = false;
		else if (node->token_type == TYPE_COMMAND && is_filename == false)
			cmd_len += 1;
		else
			is_filename = true;
		node = node->next;
	}
	return (cmd_len);
}

t_redirect	*redirect_append(t_redirect *redirect_head, char *content,
		TokenType token_type)
{
	t_redirect	*new_node;
	t_redirect	*ptr_temp;

	new_node = NULL;
	new_node = redirect_init(new_node);
	new_node->filename = content;
	new_node->token_type = token_type;
	ptr_temp = redirect_head;
	while (ptr_temp->next != NULL)
	{
		ptr_temp = ptr_temp->next;
	}
	ptr_temp->next = new_node;
	return (redirect_head);
}

t_cmd_invoke	*make_cmd(t_linked_list *list_head, t_cmd_invoke *cmd_head)
{
	t_linked_list	*list_ptr_temp;
	t_cmd_invoke	*cmd_ptr_temp;
	bool			is_filename;
	TokenType		bef_token_type;
	bool			is_pipe;
	size_t			cmd_len;
	size_t			i;

	is_filename = false;
	bef_token_type = TYPE_COMMAND;
	is_pipe = true;
	list_ptr_temp = list_head->next;
	cmd_ptr_temp = cmd_head;
	while (list_ptr_temp)
	{
		if (is_pipe)
		{
			cmd_ptr_temp->next = cmd_invoke_init(cmd_ptr_temp->next);
			cmd_ptr_temp = cmd_ptr_temp->next;
			is_pipe = false;
			is_filename = false;
			cmd_len = ft_cmd_len(list_ptr_temp);
			cmd_ptr_temp->cmd_list = (char **)malloc(sizeof(char *) * (cmd_len
						+ 1));
			cmd_ptr_temp->cmd_list[cmd_len] = NULL;
			i = 0;
		}
		if (list_ptr_temp->token_type == TYPE_PIPE)
		{
			is_pipe = true;
			free1dim(&(list_ptr_temp->content));
		}
		else if (list_ptr_temp->token_type == TYPE_COMMAND
			&& is_filename == false)
		{
			// add to cmd_list
			cmd_ptr_temp->cmd_list[i] = list_ptr_temp->content;
			i += 1;
		}
		else if (list_ptr_temp->token_type == TYPE_COMMAND
			&& is_filename == true)
		{
			redirect_append(cmd_ptr_temp->redirect_head, list_ptr_temp->content,
				bef_token_type);
			is_filename = false;
			bef_token_type = TYPE_COMMAND;
		}
		else if (list_ptr_temp->token_type == TYPE_REDIRECT_IN
			|| list_ptr_temp->token_type == TYPE_HEREDOC
			|| list_ptr_temp->token_type == TYPE_REDIRECT_OUT
			|| list_ptr_temp->token_type == TYPE_REDIRECT_APPEND)
		{
			bef_token_type = list_ptr_temp->token_type;
			is_filename = true;
			free1dim(&(list_ptr_temp->content));
		}
		list_ptr_temp = list_ptr_temp->next;
	}
	return (cmd_head);
}
