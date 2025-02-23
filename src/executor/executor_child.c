/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:12:00 by karai             #+#    #+#             */
/*   Updated: 2025/02/23 16:50:52 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_execute_child1(t_cmd_invoke *head, t_cmd_invoke *temp_ptr,
		bool is_first, char **env)
{
	heredoc_close_nu(head, temp_ptr);
	set_sig_handler_child();
	handle_command_execution(temp_ptr, is_first);
	handle_open_redirect(head, temp_ptr, env);
	if (temp_ptr->cmd_list[0] == NULL)
	{
		free_all(&head);
		free_env(env);
		exit(0);
	}
}

void	cmd_execute_child2(t_cmd_invoke *head, t_cmd_invoke *temp_ptr,
		int last_status, char **env)
{
	int	status;

	if (!is_internal_commands(temp_ptr->cmd_list[0]))
		process_cmd_invoke(temp_ptr, env, head);
	else
	{
		exit_child(head, temp_ptr, &env, last_status);
		status = handle_internal_commands(temp_ptr, &env);
		free_all(&head);
		free_env(env);
		exit(status);
	}
}
