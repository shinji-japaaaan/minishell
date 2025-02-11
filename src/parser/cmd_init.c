/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:53:20 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/11 17:50:12 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect	*redirect_init(t_redirect *new_node)
{
	new_node = (t_redirect *)malloc(sizeof(t_redirect));
	if (new_node == NULL)
		return (NULL);
	new_node->filename = NULL;
	new_node->token_type = TYPE_DEFAULT;
	new_node->fd = -1;
	new_node->stdio_backup = -1;
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
		{
			if (node->content != NULL)
				cmd_len += 1;
		}
		else
			is_filename = true;
		node = node->next;
	}
	return (cmd_len);
}

void	init_cmd_list(t_cmd_state *state)
{
	state->cmd_len = ft_cmd_len(state->list_ptr_temp);
	state->cpt->cmd_list = (char **)malloc(sizeof(char *) * (state->cmd_len
				+ 1));
	state->cpt->cmd_list[state->cmd_len] = NULL;
	state->i = 0;
}

t_cmd_invoke	*cmd_invoke_init(t_cmd_invoke *new_node)
{
	new_node = (t_cmd_invoke *)malloc(sizeof(t_cmd_invoke));
	if (new_node == NULL)
		return (NULL);
	new_node->cmd_list = NULL;
	new_node->redirect_head = NULL;
	new_node->redirect_head = redirect_init(new_node->redirect_head);
	if (new_node->redirect_head == NULL)
		return (free(new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}

t_cmd_invoke	*init_new_cmd(t_cmd_invoke *cmd_ptr_temp)
{
	cmd_ptr_temp->next = cmd_invoke_init(cmd_ptr_temp->next);
	if (cmd_ptr_temp->next == NULL)
		return (NULL);
	cmd_ptr_temp = cmd_ptr_temp->next;
	return (cmd_ptr_temp);
}
