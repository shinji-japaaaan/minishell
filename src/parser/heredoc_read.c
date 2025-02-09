/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:36:42 by karai             #+#    #+#             */
/*   Updated: 2025/02/09 13:37:34 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_read_loop(char *str_eof, char **env, int pipefd[2],
		int *last_status)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			if (g_signal == SIGINT)
				return (*last_status = 130, (void)0);
			ft_putstr_fd("bash: warning: here-document delimited", 2);
			ft_putstr_fd(" by end-of-filewanted '", 2);
			ft_putstr_fd(str_eof, 2);
			ft_putstr_fd("')\n", 2);
			return ;
		}
		if (ft_strcmp(line, str_eof) == 0)
			return (free(line), (void)0);
		line = heredoc_expansion(line, env, last_status);
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
}

void	heredoc_read(t_redirect *node, char *str_eof, char **env,
		int *last_status)
{
	int	pipefd[2];
	int	stdio_backup;

	if (pipe(pipefd) < 0)
		perror("heredoc pipe failed");
	stdio_backup = dup(0);
	heredoc_read_loop(str_eof, env, pipefd, last_status);
	dup2(stdio_backup, 0);
	close(stdio_backup);
	close(pipefd[1]);
	node->fd = pipefd[0];
}
