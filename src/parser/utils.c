/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:20:24 by karai             #+#    #+#             */
/*   Updated: 2025/02/01 09:55:10 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	ft_strcpy(char *dst, char *src)
{
	if (dst == NULL || src == NULL)
		return ;
	while (*src)
	{
		*dst = *src;
		dst += 1;
		src += 1;
	}
}
