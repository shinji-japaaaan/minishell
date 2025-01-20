/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:00:06 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/19 07:35:03 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stddef.h>
#include "../libft/libft.h"
#include "history.h"  // history.h をインクルード
#include "parser.h"
#include "builtins.h"
#include "executor.h"

#endif /* MINISHELL_H */

