/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:09:45 by karai             #+#    #+#             */
/*   Updated: 2025/02/20 21:40:28 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path_cmd(char *path_env, char **cmd, t_cmd_invoke *head,
		char **env)
{
	char	**dir_array;
	char	*full_path;
	int		i;
	int		access_status;

	dir_array = ft_split(path_env, ':');
	free(path_env);
	i = -1;
	while (dir_array[++i])
	{
		full_path = get_path_cmd_part(dir_array, cmd, i);
		access_status = is_access(full_path);
		if (access_status == 2)
			return (free2dim(&dir_array), full_path);
		free(full_path);
		if (access_status == 1)
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(" Permission denied", 2);
			fext_incmdpath(dir_array, head, env, NO_PERMISSION);
		}
	}
	ft_putstr_fd(cmd[0], 2);
	ft_putendl_fd(" command not found", 2);
	return (fext_incmdpath(dir_array, head, env, NON_COMMAND), NULL);
}

char	*get_path_cmd_part(char **dir_array, char **cmd, size_t i)
{
	char	*full_path;
	char	*tmp_str;

	tmp_str = ft_strjoin(dir_array[i], "/");
	if (tmp_str == NULL)
		perror_exit("malloc failed", dir_array, cmd, 1);
	full_path = ft_strjoin(tmp_str, cmd[0]);
	free(tmp_str);
	if (full_path == NULL)
		perror_exit("malloc failed", dir_array, cmd, 1);
	return (full_path);
}

char	*get_path_cmd_not_find_path(char **cmd, t_cmd_invoke *head, char **env)
{
	char	*full_path;
	int		access_status;

	access_status = is_access(cmd[0]);
	if (access_status == 2)
	{
		full_path = cmd[0];
		return (full_path);
	}
	if (access_status == 1)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(" Permission denied", 2);
		fext_incmdpath(NULL, head, env, NO_PERMISSION);
	}
	perror(cmd[0]);
	fext_incmdpath(NULL, head, env, NON_COMMAND);
	return (NULL);
}

void	is_directory(t_cmd_invoke *node, char **env, t_cmd_invoke *head)
{
	struct stat	file_stat;

	stat(node->cmd_list[0], &file_stat);
	if (S_ISDIR(file_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->cmd_list[0], 2);
		ft_putendl_fd(" Is a directory", 2);
		fext_incmdpath(NULL, head, env, NO_PERMISSION);
	}
}

char	*get_path_main(t_cmd_invoke *node, char **env, t_cmd_invoke *head)
{
	char	*path_env;

	if (is_full_relative_path(node->cmd_list[0]) == false)
	{
		path_env = ft_getenv("PATH", env);
		if (path_env == NULL)
		{
			is_directory(node, env, head);
			return (get_path_cmd_not_find_path(node->cmd_list, head, env));
		}
		return (get_path_cmd(path_env, node->cmd_list, head, env));
	}
	else
	{
		is_directory(node, env, head);
		return (get_path_cmd_not_find_path(node->cmd_list, head, env));
	}
}
