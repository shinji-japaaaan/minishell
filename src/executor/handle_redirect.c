/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:11:51 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 13:41:43 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_redirect_out(t_redirect *node, bool is_parent)
{
	int	fd;

	if (is_parent)
	{
		node->stdio_backup = dup(STDOUT_FILENO);
		if (node->stdio_backup == -1)
			return (perror("Error saving STDOUT"), EXIT_FAILURE);
	}
	fd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening file for output");
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd);
		return (EXIT_FAILURE);
	}
	if (close(fd) == -1)
		return (perror("Error close"), EXIT_FAILURE);
	return (0);
}

int	handle_redirect_append(t_redirect *node, bool is_parent)
{
	int	fd;

	if (is_parent)
	{
		node->stdio_backup = dup(STDOUT_FILENO);
		if (node->stdio_backup == -1)
		{
			perror("Error saving STDOUT");
			return (EXIT_FAILURE);
		}
	}
	fd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (perror("Error opening file for output"), EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd);
		return (EXIT_FAILURE);
	}
	if (close(fd) == -1)
		return (perror("Error close"), EXIT_FAILURE);
	return (0);
}

int	handle_redirect_in(t_redirect *node, bool is_parent)
{
	int	fd;

	if (is_parent)
	{
		node->stdio_backup = dup(STDIN_FILENO);
		if (node->stdio_backup == -1)
			return (perror("Error saving STDIN"), EXIT_FAILURE);
	}
	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file for input");
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error redirecting input");
		close(fd);
		return (EXIT_FAILURE);
	}
	if (close(fd) == -1)
		return (perror("Error close"), EXIT_FAILURE);
	return (0);
}

int	handle_redirect_heredoc(t_redirect *node, bool is_parent)
{
	if (is_parent)
	{
		node->stdio_backup = dup(STDIN_FILENO);
		if (node->stdio_backup == -1)
		{
			perror("Error saving STDIN");
			return (EXIT_FAILURE);
		}
	}
	if (dup2(node->fd, STDIN_FILENO) == -1)
	{
		perror("Error heredoc input");
		close(node->fd);
		return (EXIT_FAILURE);
	}
	if (close(node->fd) == -1)
	{
		perror("Error close");
		return (EXIT_FAILURE);
	}
	return (0);
}

int	handle_redirect(t_TokenType token_type, t_redirect *node, bool is_parent)
{
	int	status;

	if (node->filename == NULL)
	{
		ft_putendl_fd("minishell: ambiguous redirect", 2);
		return (1);
	}
	if (token_type == TYPE_REDIRECT_OUT)
		status = handle_redirect_out(node, is_parent);
	else if (token_type == TYPE_REDIRECT_APPEND)
		status = handle_redirect_append(node, is_parent);
	else if (token_type == TYPE_REDIRECT_IN)
		status = handle_redirect_in(node, is_parent);
	else if (token_type == TYPE_HEREDOC)
		status = handle_redirect_heredoc(node, is_parent);
	return (status);
}
