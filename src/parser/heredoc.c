/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:25:28 by karai             #+#    #+#             */
/*   Updated: 2025/02/01 10:03:16 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_read(t_redirect *node, char *str_eof)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		perror("heredoc pipe failed");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, str_eof) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	node->fd = pipefd[0];
}

void	heredoc_redirect_list(t_redirect *head_redirect_in)
{
	t_redirect	*temp_ptr;

	temp_ptr = head_redirect_in->next;
	while (temp_ptr)
	{
		if (temp_ptr->token_type == TYPE_HEREDOC)
		{
			heredoc_read(temp_ptr, temp_ptr->filename);
		}
		temp_ptr = temp_ptr->next;
	}
}

void	heredoc_main(t_cmd_invoke *head_cmd)
{
	t_cmd_invoke	*temp_ptr;

	temp_ptr = head_cmd->next;
	while (temp_ptr)
	{
		heredoc_redirect_list(temp_ptr->redirect_head);
		temp_ptr = temp_ptr->next;
	}
}

void	heredoc_close(t_cmd_invoke *node)
{
	t_redirect	*temp_ptr;

	temp_ptr = node->redirect_head;
	while (temp_ptr)
	{
		if (temp_ptr->token_type == TYPE_HEREDOC)
		{
			if (close(temp_ptr->fd) == -1)
				perror("close failed");
		}
		temp_ptr = temp_ptr->next;
	}
}

// void	heredoc_read_main(t_redirect *head_redirect)
// {
// 	t_cmd_invoke	*temp_ptr;

// 	temp_ptr = head_redirect->next;
// 	while (temp_ptr)
// 	{
// 		heredoc_read_rev(temp_ptr, temp_ptr->filename);
// 		temp_ptr = temp_ptr->next;
// 	}
// }

// void	heredoc_read_rev(t_redirect *node, char *str_eof)
// {
// 	char	*line;

// 	setup_signal_handler();
// 	while (1)
// 	{
// 		// setup_signal_handler();
// 		line = readline("> ");
// 		if (line == NULL)
// 			break ;
// 		if (strcmp(line, str_eof) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		ft_putendl_fd(line, node->fd1);
// 		free(line);
// 	}
// 	close(pipefd[1]);
// }

// void	heredoc_pipe_open(t_redirect *head_redirect)
// {
// 	t_redirect	*temp_ptr;
// 	int			pipefd[2];

// 	head_redirect->next;
// 	while (temp_ptr)
// 	{
// 		if (temp_ptr->token_type == TYPE_HEREDOC)
// 		{
// 			if (pipe(pipefd) < 0)
// 				perror("heredoc pipe failed");
// 			temp_ptr->fd = pipefd[0];
// 			temp_ptr->fd1 = pipefd[1];
// 		}
// 		temp_ptr = temp_ptr->next;
// 	}
// }
