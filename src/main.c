/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 07:59:43 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/09 14:07:22 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env(char **env)
{
	int	i;

	if (!env)
	{
		return ;
	}
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**duplicate_env(char **envp)
{
	int		count;
	char	**env;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	env = malloc((count + 1) * sizeof(char *));
	if (!env)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < count)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			perror("strdup failed");
			while (--i >= 0)
				free(env[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	env[count] = NULL;
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	(void)argc;
	(void)argv;
	env = duplicate_env(envp);
	process_shell(&env);
	free_env(env);
	return (0);
}
