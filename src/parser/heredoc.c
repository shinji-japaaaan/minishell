/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:25:28 by karai             #+#    #+#             */
/*   Updated: 2025/01/24 19:43:22 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void heredoc_read(t_redirect *node, char *str_eof)
{
	char *line;
	int pipefd[2];

	if (pipe(pipefd) < 0)
		perror("heredoc pipe failed");
	while(1)
	{
		line = readline("> ");
		if (line == NULL)
			break;
		if (strcmp(line, str_eof) == 0)
		{
			free(line);
			break;
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
		heredoc_redirect_list(temp_ptr->redirect_in_head);
		temp_ptr = temp_ptr->next;
	}
}
