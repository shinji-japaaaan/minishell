/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 06:10:02 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/22 07:23:15 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		g_signal = 0;

void	execute_shell_command(t_cmd_invoke *parsed_list, int *last_status,
		char ***env, t_History *history)
{
	int	red_status;

	if (is_internal_commands(parsed_list->next->cmd_list[0])
		&& parsed_list->next->next == NULL)
	{
		heredoc_main(parsed_list, *env, last_status);
		if (g_signal != SIGINT)
		{
			red_status = open_redirect(parsed_list->next, true);
			if (red_status == 0)
				*last_status = handle_internal_commands(parsed_list->next, env,
						*last_status);
			else
				*last_status = red_status;
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
	if (g_signal == SIGINT)
		*last_status = 130;
	if (*input == '\0' || is_empty_line(input))
	{
		free(input);
		return ;
	}
	g_signal = 0;
	handle_input(input, history, last_status, env);
}

char	*get_history_path(char **env)
{
	char	*home;
	char	*history_path;

	home = ft_getenv("HOME", env);
	if (!home)
		return (ft_strdup(".minishell_history"));
	history_path = ft_strjoin(home, "/.minishell_history");
	free(home);
	return (history_path);
}

void	process_shell(char ***env)
{
	char		*input;
	t_History	*history;
	int			last_status;

	history = init_history(MAX_HISTORY);
	history->history_path = get_history_path(*env);
	if (history->history_path)
		load_history_from_file(history->history_path, history);
	last_status = 0;
	while (1)
	{
		g_signal = 0;
		set_sig_handler_main();
		input = readline("minishell> ");
		if (!input)
			break ;
		handle_user_input(input, history, &last_status, env);
	}
	printf("%s\n", history->history_path);
	if (history->history_path)
		save_history_to_file(history->history_path, history);
	free_history(history);
	rl_clear_history();
}
