/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 08:37:11 by karai             #+#    #+#             */
/*   Updated: 2025/02/07 20:20:00 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	while (str[i] && is_name_character(str[i]))
		i++;
	*len = i;
	env_str = (char *)malloc(sizeof(char) * (i + 1));
	if (!env_str)
		return (NULL);
	while (i--)
		env_str[i] = str[i];
	env_str[*len] = '\0';
	return (env_str);
}

char	*get_env_value(char *env_str, int last_status, char **env)
{
	if (ft_strcmp(env_str, "?") == 0)
		return (ft_itoa(last_status));
	return (ft_getenv(env_str, env));
}

char	*replace_env(char *str, char *env_str, char *env_val)
{
	size_t	new_len;
	char	*new_str;
	size_t	i;

	new_len = ft_strlen(str) - ft_strlen(env_str) - 1 + ft_strlen(env_val);
	new_str = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str == '$' && ft_strncmp(str + 1, env_str,
				ft_strlen(env_str)) == 0)
		{
			ft_strcpy(&new_str[i], env_val);
			i += ft_strlen(env_val);
			str += ft_strlen(env_str) + 1;
		}
		else
			new_str[i++] = *str++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*replace_env_var(char *str, char *env_str, int last_status, char **env)
{
	char	*env_val;
	char	*new_str;

	env_val = get_env_value(env_str, last_status, env);
	if (!env_val)
		env_val = "";
	new_str = replace_env(str, env_str, env_val);
	free(env_str);
	free(str);
	return (new_str);
}

char	*handle_dollar(char *str, size_t *i, int last_status, char **env)
{
	char	*env_str;
	size_t	len;

	env_str = NULL;
	if (str[*i + 1] == '?')
	{
		env_str = (char *)malloc(sizeof(char) * 2);
		if (!env_str)
			return (NULL);
		env_str[0] = '?';
		env_str[1] = '\0';
	}
	else if (!(str[*i + 1] == '\0' || is_blank(str[*i + 1])))
	{
		env_str = get_env_str(&str[*i + 1], &len);
	}
	if (env_str != NULL)
	{
		str = replace_env_var(str, env_str, last_status, env);
		*i = -1;
	}
	return (str);
}

char	*expansion(char *str, int last_status, char **env)
{
	size_t	i;
	int		state;

	if (!str)
		return (NULL);
	i = 0;
	state = 0;
	while (str[i])
	{
		if (state == 0 && str[i] == '\'')
			state = 1;
		else if (state == 0 && str[i] == '\"')
			state = 2;
		else if (state == 1 && str[i] == '\'')
			state = 0;
		else if (state == 2 && str[i] == '\"')
			state = 0;
		else if (state != 1 && str[i] == '$' && (str[i + 1] == '?'
				|| is_name_character(str[i + 1])))
			str = handle_dollar(str, &i, last_status, env);
		i++;
	}
	return (str);
}
