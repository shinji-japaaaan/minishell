/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 08:37:11 by karai             #+#    #+#             */
/*   Updated: 2025/01/18 13:22:24 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

bool	is_name_character(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	else
		return (false);
}

char	*get_env_str(char *str, size_t *len)
{
	size_t	i;
	char	*env_str;

	*len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_name_character(str[i]) == false)
		{
			break ;
		}
		i += 1;
	}
	env_str = (char *)malloc(sizeof(char) * (i + 1));
	*len = i;
	i = 0;
	while (i < *len)
	{
		env_str[i] = str[i];
		i += 1;
	}
	env_str[i] = '\0';
	printf("Extracted environment variable name: %s, Length: %zu\n", env_str, *len);
	return (env_str);
}

char	*replace_to_env_val(char *str, char *env_str)
{
	size_t	env_str_len;
	size_t	new_len;
	size_t	env_val_len;
	char	*env_val;
	char	*new_str;
	size_t	i;
	char	*str_bef;

	str_bef = str;
	env_str_len = strlen(env_str);
	env_val = getenv(env_str);
	if (env_val == NULL)
		env_val_len = 0;
	else
		env_val_len = strlen(env_val);
	new_len = strlen(str) - env_str_len - 1 + env_val_len;
	new_str = (char *)malloc(sizeof(char) * (new_len + 1));
	i = 0;
	while (*str)
	{
		if (*str == '$' && strncmp(str + 1, env_str, env_str_len) == 0)
		{
			// デバッグ情報を追加
            printf("Replacing $%s with %s\n", env_str, env_val ? env_val : "(NULL)");
			ft_strcpy(&new_str[i], env_val);
			i += env_val_len;
			str += (env_str_len + 1);
		}
		else
		{
			new_str[i] = *str;
			str += 1;
			i += 1;
		}
	}
	new_str[i] = '\0';
	free(env_str);
	free(str_bef);
	return (new_str);
}

char	*expansion(char *str)
{
	char	*env_str;
	size_t	len;
	size_t	i;
	// char	*str_temp;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (str[0] == '\'')
		return (str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			// デバッグ情報を追加
            printf("Found $ at position %zu\n", i);
			if (!(str[i + 1] == '\0' || is_blank(str[i + 1])))
			{
				env_str = get_env_str(&str[i + 1], &len);
				str = replace_to_env_val(str, env_str);
				i = -1;
			}
		}
		i += 1;
	}
	return (str);
}

