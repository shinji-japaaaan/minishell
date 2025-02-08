/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 07:59:43 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/08 14:01:12 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env(char **env)
{
	if (!env)
	{
		return ;
	}
	int i = 0;
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

	count = 0;
	while (envp[count])
		count++;
	env = malloc((count + 1) * sizeof(char *));
	if (!env)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	int i = 0;
	while (i < count)
	{
		env[i] = strdup(envp[i]);
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
	(void)argc;
	(void)argv;
	char **env = duplicate_env(envp);
	process_shell(&env);
	free_env(env);
	return (0);
}

