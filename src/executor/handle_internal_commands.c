/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_internal_commands.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:09:29 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/09 14:12:23 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_internal_commands(t_cmd_invoke *parsed_list, char ***env)
{
	char	*cmd;
	char	**args;
	int		result;

	cmd = parsed_list->cmd_list[0];
	args = parsed_list->cmd_list;
	result = 0;
	if (ft_strcmp(cmd, "cd") == 0)
		result = change_directory(args[1], args);
	else if (ft_strcmp(cmd, "exit") == 0)
		exit_shell(args);
	else if (ft_strcmp(cmd, "echo") == 0)
		echo_command(args);
	else if (ft_strcmp(cmd, "pwd") == 0)
		result = print_working_directory();
	else if (ft_strcmp(cmd, "env") == 0)
		print_environment(*env);
	else if (ft_strcmp(cmd, "export") == 0)
		result = export_variable(env, args[1]);
	else if (ft_strcmp(cmd, "unset") == 0)
		result = unset_variable(env, args[1]);
	return (result);
}

bool	is_internal_commands(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (true);
	else if (ft_strcmp(command, "exit") == 0)
		return (true);
	else if (ft_strcmp(command, "echo") == 0)
		return (true);
	else if (ft_strcmp(command, "pwd") == 0)
		return (true);
	else if (ft_strcmp(command, "env") == 0)
		return (true);
	else if (ft_strncmp(command, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(command, "unset", 5) == 0)
		return (true);
	else
		return (false);
}
