/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:25:28 by karai             #+#    #+#             */
/*   Updated: 2025/02/09 13:37:09 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_redirect_list(t_redirect *head_redirect_in, char **env,
		int *last_status)
{
	t_redirect	*temp_ptr;

	temp_ptr = head_redirect_in->next;
	while (temp_ptr)
	{
		if (temp_ptr->token_type == TYPE_HEREDOC)
		{
			heredoc_read(temp_ptr, temp_ptr->filename, env, last_status);
			if (g_signal == SIGINT)
				break ;
		}
		temp_ptr = temp_ptr->next;
	}
}

void	heredoc_main(t_cmd_invoke *head_cmd, char **env, int *last_status)
{
	t_cmd_invoke	*temp_ptr;

	set_sig_during_heredoc();
	temp_ptr = head_cmd->next;
	while (temp_ptr)
	{
		heredoc_redirect_list(temp_ptr->redirect_head, env, last_status);
		if (g_signal == SIGINT)
			break ;
		temp_ptr = temp_ptr->next;
	}
	if (g_signal == SIGINT)
	{
		temp_ptr = head_cmd->next;
		while (temp_ptr)
		{
			heredoc_close(temp_ptr);
			temp_ptr = temp_ptr->next;
		}
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

void	heredoc_close_nu(t_cmd_invoke *head_cmd, t_cmd_invoke *now)
{
	t_cmd_invoke	*temp_ptr;
	bool			is_delete;

	is_delete = false;
	temp_ptr = head_cmd->next;
	while (temp_ptr)
	{
		if (temp_ptr == now)
			is_delete = true;
		else if (is_delete)
			heredoc_close(temp_ptr);
		temp_ptr = temp_ptr->next;
	}
}

char	*heredoc_expansion(char *input, char **env, int *last_status)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && (input[i + 1] == '?' || is_nc(input[i + 1])))
			input = handle_dollar(input, &i, *last_status, env);
		i += 1;
	}
	return (input);
}
