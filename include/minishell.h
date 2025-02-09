/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:00:06 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/09 22:08:45 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "builtins.h"
# include "executor.h"
# include "history.h" // history.h をインクルード
# include "parser.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int	g_signal;
void		process_shell(char ***env);
void		sig_handler_main(int signum);
void		disable_echoctl(void);
void		set_sig_handler_main(void);
void		set_sig_handler_child(void);
void		set_sig_during_exec(void);
void		sig_during_exec(int signum);
void		set_sig_during_heredoc(void);
void		sig_during_heredoc(int signum);
void		execute_shell_command(t_cmd_invoke *parsed_list, int *last_status,
				char ***env, t_History *history);

#endif /* MINISHELL_H */
