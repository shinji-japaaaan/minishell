/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:29:31 by karai             #+#    #+#             */
/*   Updated: 2025/02/09 13:35:41 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	process_command_token(t_cmd_state *state)
{
	if (state->is_filename == false)
	{
		state->cmd_ptr_temp->cmd_list[state->i] = state->list_ptr_temp->content;
		state->i += 1;
	}
	else
	{
		redirect_append(state->cmd_ptr_temp->redirect_head,
			state->list_ptr_temp->content, state->bef_token_type);
		state->is_filename = false;
		state->bef_token_type = TYPE_COMMAND;
	}
}

void	process_token(t_cmd_state *state, TokenType type)
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

void	process_list_ptr_temp(t_cmd_state *state)
{
	if (state->is_pipe)
	{
		state->cmd_ptr_temp = init_new_cmd(state->cmd_ptr_temp);
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
		process_command_token(state);
	}
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
		process_list_ptr_temp(&state);
		state.list_ptr_temp = state.list_ptr_temp->next;
	}
	return (cmd_head);
}
