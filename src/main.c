/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 07:59:43 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/09 17:38:38 by sishizaw         ###   ########.fr       */
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

void	handle_malloc_failure(void)
{
	perror("malloc failed");
	exit(EXIT_FAILURE);
}

void	handle_strdup_failure(char **env, int i)
{
	perror("strdup failed");
	while (--i >= 0)
		free(env[i]);
	free(env);
	exit(EXIT_FAILURE);
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
		handle_malloc_failure();
	i = 0;
	while (i < count)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			handle_strdup_failure(env, i);
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
