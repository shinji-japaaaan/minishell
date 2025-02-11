/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:40:24 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/11 10:13:29 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	change_directory(char *path, char **args, char ***env)
{
	char	*current_dir;

	if (args[1] && args[2])
		return (print_error("cd: too many arguments\n"));
	path = resolve_path(path);
	if (!path)
		return (print_error("cd failed: HOME not set\n"));
	if (chdir(path) == -1)
	{
		perror("cd failed");
		return (1);
	}
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (1);
	if (update_pwd_env_var(env, current_dir) != 0)
		return (free(current_dir), 1);
	free(current_dir);
	return (0);
}

void	exit_shell(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1] && args[2])
	{
		put_str(STDERR_FILENO, "exit: too many arguments\n");
		exit(1);
	}
	if (args[1])
	{
		if (!is_numeric(args[1]))
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

void	echo_command(char **args)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	i = 1;
	if (!args || !args[0])
		return ;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0
		&& ft_strlen(args[i]) == 2)
	{
		no_newline = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
		{
			printf(" ");
		}
		i++;
	}
	if (!no_newline)
		printf("\n");
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
