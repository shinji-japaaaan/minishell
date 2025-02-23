/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:40:24 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/23 14:19:30 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	change_directory(char *path, char **args, char ***env)
{
	char	*current_dir;

	if (args[1] && args[2])
		return (print_error("cd: too many arguments\n"));
	path = resolve_path(path, env);
	if (!path)
		return (print_error("cd failed: HOME not set\n"));
	if (chdir(path) == -1)
	{
		perror("cd failed");
		return (1);
	}
	free(path);
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (1);
	if (update_pwd_env_var(env, current_dir) != 0)
		return (free(current_dir), 1);
	free(current_dir);
	return (0);
}

bool	is_within_long(char *np)
{
	long long	a;
	int			pm;

	a = 0;
	pm = 1;
	while (*np == '\f' || *np == '\n' || *np == '\r' || *np == '\t'
		|| *np == '\v' || *np == ' ')
		np += 1;
	if (*np == '-')
		pm = -1;
	if (*np == '-' || *np == '+')
		np += 1;
	while (*np != '\0')
	{
		if (!(*np <= '9' && *np >= '0'))
			return (false);
		if (pm == 1 && (a > LLONG_MAX / 10 || ((LLONG_MAX - a * 10) < (*np
						- '0'))))
			return (false);
		if (a != 0 && pm == -1 && ((a > -1 * (LLONG_MIN / 10)) || (-1
					* (LLONG_MIN + a * 10)) < (*np - '0')))
			return (false);
		a = a * 10 + (*np++ - '0');
	}
	return (true);
}

void	exit_shell(char **args, int exit_code)
{
	if (args[1] && args[2])
	{
		put_str(STDERR_FILENO, "exit: too many arguments\n");
		exit(1);
	}
	if (args[1])
	{
		if (!is_numeric(args[1]) || !is_within_long(args[1]))
		{
			put_str(STDERR_FILENO, "exit: ");
			put_str(STDERR_FILENO, args[1]);
			put_str(STDERR_FILENO, ": numeric argument required\n");
			exit(2);
		}
		exit_code = ft_atoi(args[1]);
	}
	exit(exit_code);
}

int	print_working_directory(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd failed");
		return (1);
	}
}
