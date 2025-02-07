/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:30:44 by karai             #+#    #+#             */
/*   Updated: 2025/02/07 19:27:40 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cmp_for_getenv(char *str, char *env_str, size_t *len)
{
	size_t	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0' && env_str[i] != '\0')
	{
		if (env_str[i] != str[i])
			return (str[i] - env_str[i]);
		i += 1;
	}
	if (str[i] == '\0' && env_str[i] == '=')
	{
		*len = i + 1;
		return (0);
	}
	return (1);
}

char	*ft_getenv(char *str, char **env)
{
	size_t	i;
	char	*path_line;
	size_t	len;

	i = 0;
	while (env[i])
	{
		if (ft_cmp_for_getenv(str, env[i], &len) == 0)
		{
			path_line = ft_strdup(&(env[i][len]));
			return (path_line);
		}
		i += 1;
	}
	return (NULL);
}
