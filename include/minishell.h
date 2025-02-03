/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:00:06 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/02 18:01:35 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/libft/libft.h"
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
# include <unistd.h>
# include <termios.h>

// extern int		interrupted;

extern pid_t	global_pid;
void			setup_signal_handler(void);
// void	handle_sigint(int signum, siginfo_t *info, void *context);
void			handle_sigint(int signum);

#endif /* MINISHELL_H */
