/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:45:13 by karai             #+#    #+#             */
/*   Updated: 2025/02/06 05:29:44 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	get_new_len_without_quotes(char *str)
{
	size_t	len;
	size_t	i;
	int		state;

	len = 0;
	i = 0;
	state = 0;
	while (str[i])
	{
		if (state == 0 && (str[i] == '\'' || str[i] == '\"'))
			state = (str[i] == '\'') + 1;
		else if ((state == 1 && str[i] == '\'') || (state == 2 && str[i] == '\"'))
			state = 0;
		else
			len++;
		i++;
	}
	return (len);
}

char	*copy_without_quotes(char *str, char *new_str)
{
	size_t	i;
	size_t	j;
	int		state;

	i = 0;
	j = 0;
	state = 0;
	while (str[i])
	{
		if (state == 0)
		{
			if (str[i] == '\'')
				state = 1;
			else if (str[i] == '\"')
				state = 2;
			else
				new_str[j++] = str[i];
		}
		else if ((state == 1 && str[i] == '\'') || (state == 2 && str[i] == '\"'))
			state = 0;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*remove_quote(char *str)
{
	char	*new_str;
	size_t	new_len;

	new_len = get_new_len_without_quotes(str);
	new_str = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new_str)
		return (NULL);
	new_str = copy_without_quotes(str, new_str);
	free(str);
	return (new_str);
}


