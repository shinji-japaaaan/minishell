/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:20:24 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 10:10:59 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_nc(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	else
		return (false);
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

bool	is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	else
		return (false);
}

void	ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
