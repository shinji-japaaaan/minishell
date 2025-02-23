/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:59:02 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/23 14:09:49 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_env_var(char *prefix, const char *value)
{
	size_t	len;
	char	*env_var;

	len = ft_strlen(prefix) + ft_strlen(value) + 1;
	env_var = malloc(len);
	if (!env_var)
	{
		perror("malloc failed");
		return (NULL);
	}
	ft_strcpy(env_var, prefix);
	ft_strcat(env_var, value);
	return (env_var);
}

int	add_new_env_var(char ***env, char *new_var, int i)
{
	char	**new_environ;

	new_environ = ft_realloc(*env, (i + 2) * sizeof(char *));
	if (!new_environ)
	{
		perror("realloc failed");
		free(new_var);
		return (1);
	}
	*env = new_environ;
	(*env)[i] = new_var;
	(*env)[i + 1] = NULL;
	return (0);
}

int	update_old_pwd(char ***env, char *old_pwd)
{
	size_t	len;
	char	*new_old_pwd;
	int		i;

	len = ft_strlen("OLDPWD=") + ft_strlen(old_pwd) + 1;
	new_old_pwd = malloc(len);
	i = 0;
	if (!new_old_pwd)
	{
		perror("malloc failed");
		return (1);
	}
	ft_strcpy(new_old_pwd, "OLDPWD=");
	ft_strcat(new_old_pwd, old_pwd);
	free(old_pwd);
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], "OLDPWD=", 7) == 0)
		{
			free((*env)[i]);
			(*env)[i] = new_old_pwd;
			return (0);
		}
		i++;
	}
	return (add_new_env_var(env, new_old_pwd, i));
}

int	update_or_add_env_var(char ***env, char *new_env_var)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], "PWD=", 4) == 0)
		{
			free((*env)[i]);
			(*env)[i] = new_env_var;
			return (0);
		}
		i++;
	}
	return (add_new_env_var(env, new_env_var, i));
}

int	update_pwd_env_var(char ***env, const char *new_pwd)
{
	char	*new_env_var;
	char	*old_pwd;
	int		result;

	old_pwd = ft_getenv("PWD", *env);
	if (old_pwd)
	{
		result = update_old_pwd(env, old_pwd);
		if (result != 0)
			return (result);
	}
	new_env_var = create_env_var("PWD=", new_pwd);
	if (!new_env_var)
		return (1);
	return (update_or_add_env_var(env, new_env_var));
}
