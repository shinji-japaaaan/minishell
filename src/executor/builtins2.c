/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:40:24 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/10 23:01:39 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_environment(char **env)
{
	char	**env_ptr;

	env_ptr = env;
	while (*env_ptr)
	{
		printf("%s\n", *env_ptr);
		env_ptr++;
	}
}

int	export_variable(char ***env, char *arg)
{
	int		i;
	size_t	name_len;

	if (!arg)
		return (print_and_return(*env));
	if (!is_valid_identifier(arg))
		return (handle_invalid_identifier(arg));
	if (!ft_strchr(arg, '='))
		return (0);
	i = 0;
	name_len = ft_strchr(arg, '=') - arg;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], arg, name_len) == 0
			&& (*env)[i][name_len] == '=')
			return (handle_existing_variable(env, arg, i));
		i++;
	}
	return (add_new_variable(env, arg, i));
}

int	unset_variable(char ***env, char *arg)
{
	int	i;
	int	j;

	if (arg == NULL)
	{
		return (0);
	}
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], arg, ft_strlen(arg)) == 0
			&& (*env)[i][ft_strlen(arg)] == '=')
		{
			free((*env)[i]);
		}
		else
		{
			(*env)[j++] = (*env)[i];
		}
		i += 1;
	}
	(*env)[j] = NULL;
	return (0);
}
