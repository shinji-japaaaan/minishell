/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 06:10:02 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/08 07:22:15 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

pid_t	global_pid = 0;
int		g_signal = 0;

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
	else if (strncmp(command, "export", 7) == 0)
		return (true);
	else if (strncmp(command, "unset", 5) == 0)
		return (true);
	else
		return (false);
}

void	execute_shell_command(t_cmd_invoke *parsed_list, char *command,
		int *last_status, char ***env)
{
	if (is_internal_commands(command) && parsed_list->next->next == NULL)
	{
		*last_status = heredoc_redirect_list(parsed_list->next->redirect_head,
				*env);
		if (!(*last_status))
		{
			*last_status = open_redirect(parsed_list->next, true);
			if (*last_status == 0)
				*last_status = handle_internal_commands(parsed_list->next, env);
			reset_redirect(parsed_list->next);
		}
		else
			heredoc_close(parsed_list->next);
	}
	else
		*last_status = cmd_execute_main(parsed_list, *env);
}

void	handle_input(char *input, History *history, int *last_status,
		char ***env)
{
	t_cmd_invoke	*parsed_list;
	char			*command;

	if (*input)
	{
		add_history(input);
		add_to_history(history, input);
	}
	if (parse_error_quote(input) || parse_error_unexpected_str(input))
	{
		ft_putendl_fd("syntax error", 2);
		free(input);
		return ;
	}
	parsed_list = parser(input, *last_status, *env);
	if (!parsed_list)
	{
		ft_putendl_fd("Error: Failed to parse input.", 2);
		free(input);
		return ;
	}
	command = parsed_list->next->cmd_list[0];
	execute_shell_command(parsed_list, command, last_status, env);
	free_all(&parsed_list);
	free(input);
}

void	process_shell(char ***env)
{
	char	*input;
	History	*history;
	int		last_status;

	history = init_history(MAX_HISTORY);
	load_history_from_file(HISTORY_FILE, history);
	last_status = 0;
	while (1)
	{
		global_pid = 0;
		g_signal = 0;
		set_sig_handler_main();
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		if (g_signal == SIGINT)
			last_status = 130;
		handle_input(input, history, &last_status, env);
	}
	save_history_to_file(HISTORY_FILE, history);
	free_history(history);
	rl_clear_history();
}
