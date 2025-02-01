/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 09:45:42 by karai             #+#    #+#             */
/*   Updated: 2025/02/02 06:41:27 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	parse_error_unexpected_str_judge(char *str)
{
	if (ft_strncmp(str, "||", 2) == 0 || ft_strncmp(str, "<<<", 3) == 0
		|| ft_strncmp(str, ">>>", 3) == 0)
		return (true);
	return (false);
}

bool	parse_error_unexpected_str(char *input)
{
	bool	inside_single_quote;
	bool	inside_double_quote;

	inside_single_quote = false;
	inside_double_quote = false;
	while (*input)
	{
		if (inside_double_quote && *input == '\"')
			inside_double_quote = false;
		else if (inside_single_quote && *input == '\'')
			inside_single_quote = false;
		else if (!inside_double_quote && !inside_single_quote)
		{
			if (*input == '\"')
				inside_double_quote = true;
			else if (*input == '\'')
				inside_single_quote = true;
			if (parse_error_unexpected_str_judge(input))
				return (true);
		}
		input += 1;
	}
	return (false);
}
