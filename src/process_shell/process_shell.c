/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 06:10:02 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/11 15:56:05 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		g_signal = 0;

void	free_history(t_History *history)
{
	int	i;

	if (!history)
		return ;
	if (history->entries)
	{
		i = 0;
		while (i < history->count)
		{
			free(history->entries[i]);
			i++;
		}
		free(history->entries);
	}
	free(history);
}

void	execute_shell_command(t_cmd_invoke *parsed_list, int *last_status,
		char ***env, t_History *history)
{
	if (is_internal_commands(parsed_list->next->cmd_list[0])
		&& parsed_list->next->next == NULL)
	{
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
		*last_status = cmd_execute_main(parsed_list, *env, last_status,
				history);
}

void	handle_input(char *input, t_History *history, int *last_status,
		char ***env)
{
	t_cmd_invoke	*parsed_list;

	if (*input)
	{
		add_history(input);
		add_to_history(history, input);
	}
	if (parse_error_quote(input) || parse_error_unexpected_str(input))
	{
		*last_status = 2;
		ft_putendl_fd("syntax error", 2);
		return (free(input));
	}
	parsed_list = parser(input, *last_status, *env);
	if (!parsed_list)
	{
		*last_status = 2;
		return (free(input));
	}
	execute_shell_command(parsed_list, last_status, env, history);
	free_all(&parsed_list);
	free(input);
}

void	handle_user_input(char *input, t_History *history, int *last_status,
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
	char		*input;
	t_History	*history;
	int			last_status;

	history = init_history(MAX_HISTORY);
	load_history_from_file(HISTORY_FILE, history);
	last_status = 0;
	while (1)
	{
		g_signal = 0;
		set_sig_handler_main();
		input = readline("minishell> ");
		if (!input)
			break ;
		if (g_signal == SIGINT)
			last_status = 130;
		g_signal = 0;
		handle_user_input(input, history, &last_status, env);
	}
	save_history_to_file(HISTORY_FILE, history);
	free_history(history);
	rl_clear_history();
}
