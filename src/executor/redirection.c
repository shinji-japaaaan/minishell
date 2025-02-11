/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 06:54:57 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/11 22:28:29 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_redirect(t_cmd_invoke *node, bool is_parent)
{
	int			status;
	t_redirect	*temp_ptr;

	temp_ptr = node->redirect_head->next;
	while (temp_ptr)
	{
		status = handle_redirect(temp_ptr->token_type, temp_ptr, is_parent);
		if (status != 0)
			return (status);
		temp_ptr = temp_ptr->next;
	}
	return (0);
}

void	reset_redirect_out(t_redirect *node)
{
	struct stat	st;

	if (dup2(node->stdio_backup, STDOUT_FILENO) == -1)
	{
		perror("Error restoring STDOUT");
		exit(EXIT_FAILURE);
	}
	if (fstat(node->stdio_backup, &st) == 0)
		close(node->stdio_backup);
}

void	reset_redirect_in(t_redirect *node)
{
	struct stat	st;

	if (fstat(node->stdio_backup, &st) == 0 && dup2(node->stdio_backup,
			STDIN_FILENO) == -1)
	{
		perror("Error restoring STDIN");
		exit(EXIT_FAILURE);
	}
	if (node->token_type == TYPE_HEREDOC)
	{
		if (fstat(node->fd, &st) == 0)
			close(node->fd);
	}
	if (fstat(node->stdio_backup, &st) == 0)
		close(node->stdio_backup);
}

void	reset_redirect_recursive(t_redirect *node)
{
	if (node->token_type == TYPE_REDIRECT_OUT
		|| node->token_type == TYPE_REDIRECT_APPEND)
	{
		if (node->next == NULL)
			return (reset_redirect_out(node));
		else
		{
			reset_redirect_recursive(node->next);
			reset_redirect_out(node);
			return ;
		}
	}
	else
	{
		if (node->next == NULL)
			return (reset_redirect_in(node));
		else
		{
			reset_redirect_recursive(node->next);
			reset_redirect_in(node);
			return ;
		}
	}
}

void	reset_redirect(t_cmd_invoke *node)
{
	t_redirect	*redirect_head;

	redirect_head = node->redirect_head;
	if (redirect_head->next != NULL)
	{
		reset_redirect_recursive(redirect_head->next);
	}
}
