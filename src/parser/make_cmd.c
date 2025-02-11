/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:29:31 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 17:13:39 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect	*redirect_append(t_redirect *redirect_head, char *content,
		t_TokenType token_type, bool is_quote)
{
	t_redirect	*new_node;
	t_redirect	*ptr_temp;

	new_node = NULL;
	new_node = redirect_init(new_node);
	if (new_node == NULL)
		return (NULL);
	new_node->is_quote = is_quote;
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

t_cmd_state	*process_command_token(t_cmd_state *state)
{
	if (state->is_filename == false)
	{
		if (state->list_ptr_temp->content != NULL)
		{
			state->cmd_ptr_temp->cmd_list[state->i] = state->list_ptr_temp->content;
			state->i += 1;
		}
	}
	else
	{
		if (redirect_append(state->cmd_ptr_temp->redirect_head,
				state->list_ptr_temp->content, state->bef_token_type,
				state->list_ptr_temp->is_quote) == NULL)
			return (NULL);
		state->is_filename = false;
		state->bef_token_type = TYPE_COMMAND;
	}
	return (state);
}

void	process_token(t_cmd_state *state, t_TokenType type)
{
	if (type == TYPE_PIPE)
	{
		state->is_pipe = true;
		free1dim(&(state->list_ptr_temp->content));
	}
	else if (type == TYPE_REDIRECT_IN || type == TYPE_HEREDOC
		|| type == TYPE_REDIRECT_OUT || type == TYPE_REDIRECT_APPEND)
	{
		state->bef_token_type = state->list_ptr_temp->token_type;
		state->is_filename = true;
		free1dim(&(state->list_ptr_temp->content));
	}
}

t_cmd_state	*process_list_ptr_temp(t_cmd_state *state)
{
	if (state->is_pipe)
	{
		state->cmd_ptr_temp = init_new_cmd(state->cmd_ptr_temp);
		if (state->cmd_ptr_temp == NULL)
			return (NULL);
		init_cmd_list(state);
		state->is_pipe = false;
		state->is_filename = false;
	}
	if (state->list_ptr_temp->token_type == TYPE_PIPE
		|| state->list_ptr_temp->token_type == TYPE_REDIRECT_IN
		|| state->list_ptr_temp->token_type == TYPE_HEREDOC
		|| state->list_ptr_temp->token_type == TYPE_REDIRECT_OUT
		|| state->list_ptr_temp->token_type == TYPE_REDIRECT_APPEND)
	{
		process_token(state, state->list_ptr_temp->token_type);
	}
	else if (state->list_ptr_temp->token_type == TYPE_COMMAND)
	{
		if (process_command_token(state) == NULL)
			return (NULL);
	}
	return (state);
}

t_cmd_invoke	*make_cmd(t_linked_list *list_head, t_cmd_invoke *cmd_head)
{
	t_cmd_state	state;

	state.list_ptr_temp = list_head->next;
	state.cmd_ptr_temp = cmd_head;
	state.is_filename = false;
	state.bef_token_type = TYPE_COMMAND;
	state.is_pipe = true;
	while (state.list_ptr_temp)
	{
		if (process_list_ptr_temp(&state) == NULL)
		{
			free_all(&cmd_head);
			free_linked_list_all(&list_head);
			return (NULL);
		}
		state.list_ptr_temp = state.list_ptr_temp->next;
	}
	return (cmd_head);
}
