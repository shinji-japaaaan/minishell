/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:01:07 by karai             #+#    #+#             */
/*   Updated: 2025/02/21 00:16:52 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_empty_line(char *input)
{
	while (*input)
	{
		if (*input != ' ' && *input != '\t')
			return (false);
		input += 1;
	}
	free(input);
	return (true);
}
