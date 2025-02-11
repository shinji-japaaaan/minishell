/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_handle_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:04:01 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 18:18:56 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_open_redirect(t_cmd_invoke *head, t_cmd_invoke *temp_ptr,
		char **env)
{
	int	status;

	status = open_redirect(temp_ptr, false);
	if (status != 0)
	{
		free_all(&head);
		free_env(env);
		exit(status);
	}
}

t_cmd_invoke	*cmd_pipe_connect(t_cmd_invoke *temp_ptr)
{
	if (pipe(temp_ptr->nxt_pipefd) < 0)
	{
		perror("pipe failed");
		return (NULL);
	}
	temp_ptr->next->bef_pipefd = temp_ptr->nxt_pipefd;
	return (temp_ptr);
}

void	handle_command_execution(t_cmd_invoke *temp_ptr, bool is_first)
{
	if (is_first)
	{
		if (temp_ptr->next != NULL)
			cmd_execute_first(temp_ptr);
	}
	else
	{
		if (temp_ptr->next == NULL)
			cmd_execute_last(temp_ptr);
		else
			cmd_execute_middle(temp_ptr);
	}
}
