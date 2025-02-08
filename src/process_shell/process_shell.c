/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 06:10:02 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/08 18:41:51 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		g_signal = 0;

void	execute_shell_command(t_cmd_invoke *parsed_list, char *command,
		int *last_status, char ***env)
{
	if (is_internal_commands(command) && parsed_list->next->next == NULL)
	{
		// heredoc_redirect_list(parsed_list->next->redirect_head,
		// 		*env, last_status);
		heredoc_main(parsed_list, *env, last_status);
		if (g_signal != SIGINT)
		{
			*last_status = open_redirect(parsed_list->next, true);
			if (*last_status == 0)
				*last_status = handle_internal_commands(parsed_list->next, env);
			reset_redirect(parsed_list->next);
			heredoc_close(parsed_list->next);
		}
	}
	else
		*last_status = cmd_execute_main(parsed_list, *env, last_status);
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

void	reset_global_state(void)
{
	g_signal = 0;
}

void	handle_user_input(char *input, History *history, int *last_status,
		char ***env)
{
	if (*input == '\0')
	{
		free(input);
		return ;
	}
	if (g_signal == SIGINT)
		*last_status = 130;
	handle_input(input, history, last_status, env);
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
		reset_global_state();
		set_sig_handler_main();
		input = readline("minishell> ");
		if (!input)
		{
			break ;
		}
		handle_user_input(input, history, &last_status, env);
	}
	save_history_to_file(HISTORY_FILE, history);
	free_history(history);
	rl_clear_history();
}
