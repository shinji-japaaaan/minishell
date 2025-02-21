/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:04:04 by karai             #+#    #+#             */
/*   Updated: 2025/02/21 23:12:05 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_echo_option(char *str)
{
	size_t	i;
	bool	is_option;

	if (str[0] != '-')
		return (false);
	i = 1;
	is_option = false;
	while (str[i])
	{
		if (str[i] == 'n')
			is_option = true;
		else
			return (false);
		i += 1;
	}
	return (is_option);
}

void	echo_command(char **args)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	i = 1;
	if (!args || !args[0])
		return ;
	while (args[i] && is_echo_option(args[i]))
	{
		no_newline = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
		{
			printf(" ");
		}
		i++;
	}
	if (!no_newline)
		printf("\n");
}
