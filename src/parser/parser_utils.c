/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:00:42 by karai             #+#    #+#             */
/*   Updated: 2025/01/12 15:58:16 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "parser.h"

bool	is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	else
		return (false);
}

// not implementing here doc for now
int	is_delimeter(char *str)
{
	if (str[0] == '\0')
		return (0);
	if (str[0] == '>' && str[1] == '>')
		return (2);
	if (str[0] == '<' && str[1] == '<')
		return (2);
	if (*str == '|' || *str == '<' || *str == '>')
		return (1);
	return (0);
}

char	*strdup_len(char *str, size_t n)
{
	char	*ret_str;
	size_t	i;

	ret_str = (char *)malloc(sizeof(char) * (n + 1));
	i = 0;
	while (i < n)
	{
		ret_str[i] = str[i];
		i += 1;
	}
	ret_str[i] = '\0';
	return (ret_str);
}
