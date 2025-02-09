/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:40:24 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/09 13:19:34 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_new_variable(char ***env, char *arg, int i)
{
	char	**new_env;

	new_env = ft_realloc(*env, sizeof(char *) * (i + 2));
	if (!new_env)
	{
		perror("realloc failed");
		return (1);
	}
	*env = new_env;
	(*env)[i] = ft_strdup(arg);
	if (!(*env)[i])
	{
		perror("strdup failed");
		return (1);
	}
	(*env)[i + 1] = NULL;
	return (0);
}

int	handle_existing_variable(char ***env, char *arg, int i)
{
	char	*new_entry;

	new_entry = ft_strdup(arg);
	if (!new_entry)
	{
		perror("strdup failed");
		return (1);
	}
	free((*env)[i]);
	(*env)[i] = new_entry;
	return (0);
}

int	handle_invalid_identifier(char *arg)
{
	put_str(STDERR_FILENO, "export: `");
	put_str(STDERR_FILENO, arg);
	put_str(STDERR_FILENO, "': not a valid identifier\n");
	return (1);
}

int	is_valid_identifier(const char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
	{
		return (0);
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	print_and_return(char **env)
{
	int	i;

	if (!env || !env[0])
	{
		return (0);
	}
	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i += 1;
	}
	return (0);
}
