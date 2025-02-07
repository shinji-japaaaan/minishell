/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:25:28 by karai             #+#    #+#             */
/*   Updated: 2025/02/07 20:21:39 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_interrupt(void)
{
	if (global_pid)
		rl_done = 1;
	return (0);
}

void	handle_sigint_heredoc(int signum)
{
	(void)signum;
	global_pid = 1;
}

void	setup_signal_handler_heredoc(void)
{
	global_pid = 0;
	rl_done = 0;
	signal(SIGINT, handle_sigint_heredoc);
}

void	heredoc_read(t_redirect *node, char *str_eof, char **env)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		perror("heredoc pipe failed");
	setup_signal_handler_heredoc();
	rl_event_hook = check_interrupt;
	while (!global_pid)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (global_pid || ft_strcmp(line, str_eof) == 0)
		{
			free(line);
			break ;
		}
		line = heredoc_expansion(line, env);
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	rl_event_hook = NULL;
	close(pipefd[1]);
	node->fd = pipefd[0];
}

int	heredoc_redirect_list(t_redirect *head_redirect_in, char **env)
{
	t_redirect	*temp_ptr;

	temp_ptr = head_redirect_in->next;
	while (temp_ptr)
	{
		if (temp_ptr->token_type == TYPE_HEREDOC)
		{
			heredoc_read(temp_ptr, temp_ptr->filename, env);
			if (global_pid)
				return (130);
		}
		temp_ptr = temp_ptr->next;
	}
	return (0);
}

void	heredoc_main(t_cmd_invoke *head_cmd, char **env)
{
	t_cmd_invoke	*temp_ptr;

	temp_ptr = head_cmd->next;
	while (temp_ptr)
	{
		heredoc_redirect_list(temp_ptr->redirect_head, env);
		temp_ptr = temp_ptr->next;
	}
}

void	heredoc_close(t_cmd_invoke *node)
{
	t_redirect	*temp_ptr;
	struct stat	st;

	temp_ptr = node->redirect_head;
	while (temp_ptr)
	{
		if (temp_ptr->token_type == TYPE_HEREDOC)
		{
			if (fstat(temp_ptr->fd, &st) == 0)
			{
				if (close(temp_ptr->fd) == -1)
					perror("close failed");
			}
		}
		temp_ptr = temp_ptr->next;
	}
}

char	*heredoc_expansion(char *input, char **env)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && (input[i + 1] == '?' || is_name_character(input[i
					+ 1])))
			input = handle_dollar(input, &i, 0, env);
		i += 1;
	}
	return (input);
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
