/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:36:42 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 17:42:56 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_error_mess(char *str_eof, int *last_status)
{
	if (g_signal == SIGINT)
		return (*last_status = 130, (void)0);
	ft_putstr_fd("bash: warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-filewanted '", 2);
	ft_putstr_fd(str_eof, 2);
	ft_putstr_fd("')\n", 2);
}

void	heredoc_stdio_restore(char *line, int stdio_backup, int pipefd[2],
		t_redirect *node)
{
	free(line);
	dup2(stdio_backup, 0);
	close(stdio_backup);
	close(pipefd[1]);
	node->fd = pipefd[0];
}

void	heredoc_read(t_redirect *node, char *str_eof, char **env,
		int *last_status)
{
	char	*line;
	int		pipefd[2];
	int		stdio_backup;

	if (pipe(pipefd) < 0)
		return (perror("heredoc pipe failed"));
	stdio_backup = dup(0);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			heredoc_error_mess(str_eof, last_status);
			break ;
		}
		if (ft_strcmp(line, str_eof) == 0)
			break ;
		if (node->is_quote == false)
			line = heredoc_expansion(line, env, last_status);
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	heredoc_stdio_restore(line, stdio_backup, pipefd, node);
}

// void	heredoc_read(t_redirect *node, char *str_eof, char **env,
// 		int *last_status)
// {
// 	int	pipefd[2];
// 	int	stdio_backup;

// 	if (pipe(pipefd) < 0)
// 	{
// 		perror("heredoc pipe failed");
// 		return ;
// 	}
// 	stdio_backup = dup(0);
// 	heredoc_read_loop(str_eof, env, pipefd, last_status);
// 	dup2(stdio_backup, 0);
// 	close(stdio_backup);
// 	close(pipefd[1]);
// 	node->fd = pipefd[0];
// }
