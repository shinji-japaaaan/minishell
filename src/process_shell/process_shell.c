/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 06:10:02 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/07 20:01:10 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

pid_t	global_pid = 0;

int	handle_internal_commands(t_cmd_invoke *parsed_list, char ***env)
{
	char	*command;
	char	**args;

	command = parsed_list->cmd_list[0];
	args = parsed_list->cmd_list;
	if (strcmp(command, "cd") == 0)
	{
		return (change_directory(args[1], args));
	}
	else if (strcmp(command, "exit") == 0)
	{
		return (exit_shell(args), 1);
	}
	else if (strcmp(command, "echo") == 0)
	{
		return (echo_command(args), 0);
	}
	else if (strcmp(command, "pwd") == 0)
	{
		return (print_working_directory());
	}
	else if (strcmp(command, "env") == 0)
	{
		return (print_environment(*env), 1);
	}
	else if (strcmp(command, "export") == 0)
	{
		return (export_variable(env, args[1]));
	}
	else if (strcmp(command, "unset") == 0)
	{
		return (unset_variable(env, args[1]));
	}
	else
	{
		return (0);
	}
}

bool	is_internal_commands(char *command)
{
	if (strcmp(command, "cd") == 0)
		return (true);
	else if (strcmp(command, "exit") == 0)
		return (true);
	else if (strcmp(command, "echo") == 0)
		return (true);
	else if (strcmp(command, "pwd") == 0)
		return (true);
	else if (strcmp(command, "env") == 0)
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

	setup_signal_handler();
	history = init_history(MAX_HISTORY);
	load_history_from_file(HISTORY_FILE, history);
	last_status = 0;
	while (1)
	{
		global_pid = 0;
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		handle_input(input, history, &last_status, env);
	}
	save_history_to_file(HISTORY_FILE, history);
	free_history(history);
	rl_clear_history();
}
