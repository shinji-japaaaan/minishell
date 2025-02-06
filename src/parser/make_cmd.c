/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:29:31 by karai             #+#    #+#             */
/*   Updated: 2025/02/06 21:22:45 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_cmd_invoke	*init_new_cmd(t_cmd_invoke *cmd_ptr_temp)
{
	cmd_ptr_temp->next = cmd_invoke_init(cmd_ptr_temp->next);
	cmd_ptr_temp = cmd_ptr_temp->next;
	return (cmd_ptr_temp);
}

void	init_cmd_list(t_cmd_state *state)
{
	state->cmd_len = ft_cmd_len(state->list_ptr_temp);
	state->cmd_ptr_temp->cmd_list = (char **)malloc(sizeof(char *)
		* (state->cmd_len + 1));
	state->cmd_ptr_temp->cmd_list[state->cmd_len] = NULL;
	state->i = 0;
}

void	process_pipe(t_cmd_state *state)
{
	state->is_pipe = true;
	free1dim(&(state->list_ptr_temp->content));
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

void	process_redirect_token(t_cmd_state *state)
{
	state->bef_token_type = state->list_ptr_temp->token_type;
	state->is_filename = true;
	free1dim(&(state->list_ptr_temp->content));
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
	if (state->list_ptr_temp->token_type == TYPE_PIPE)
	{
		process_pipe(state);
	}
	else if (state->list_ptr_temp->token_type == TYPE_COMMAND)
	{
		process_command_token(state);
	}
	else if (state->list_ptr_temp->token_type == TYPE_REDIRECT_IN ||
		state->list_ptr_temp->token_type == TYPE_HEREDOC ||
		state->list_ptr_temp->token_type == TYPE_REDIRECT_OUT ||
		state->list_ptr_temp->token_type == TYPE_REDIRECT_APPEND)
	{
		process_redirect_token(state);
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



