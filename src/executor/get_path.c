/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:09:45 by karai             #+#    #+#             */
/*   Updated: 2025/01/19 07:28:43 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path_cmd(char *path_env, char **cmd)
{
	char	**dir_array;
	char	*full_path;
	char	*tmp_str;
	int		i;

	dir_array = ft_split(path_env, ':');
	i = 0;
	while (dir_array[i])
	{
		tmp_str = ft_strjoin(dir_array[i], "/");
		full_path = get_path_cmd_part(dir_array, cmd, tmp_str);
		if (full_path != NULL)
			return (full_path);
		i += 1;
	}
	ft_putstr_fd(cmd[0], 2);
	ft_putendl_fd(" command not found", 2);
	free2dim(dir_array);
	exit(NON_COMMAND);
	// free_exit(dir_array, cmd, NON_COMMAND);
	return (NULL);
}

char	*get_path_cmd_part(char **dir_array, char **cmd, char *tmp_str)
{
	char	*full_path;
	int		access_status;

	if (tmp_str == NULL)
		perror_exit("malloc failed", dir_array, cmd, 1);
	full_path = ft_strjoin(tmp_str, cmd[0]);
	free(tmp_str);
	if (full_path == NULL)
		perror_exit("malloc failed", dir_array, cmd, 1);
	access_status = is_access(full_path);
	if (access_status == 2)
	{
		free2dim(dir_array);
		return (full_path);
	}
	free(full_path);
	if (access_status == 1)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(" Permission denied", 2);
		free2dim(dir_array);
		exit(NO_PERMISSION);
		// free_exit(dir_array, cmd, NO_PERMISSION);
	}
	return (NULL);
}

char	*get_path_cmd_not_find_path(char **cmd)
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
		// free2dim(cmd);
		exit(NO_PERMISSION);
	}
	perror(cmd[0]);
	// free2dim(cmd);
	exit(NON_COMMAND);
	return (NULL);
}

char	*get_path_main(t_cmd_invoke *node)
{
	char	*path_env;

	if (is_full_relative_path(node->cmd_list[0]) == false)
	{
		path_env = getenv("PATH");
		return (get_path_cmd(path_env, node->cmd_list));
		ft_putstr_fd(node->cmd_list[0], 2);
		ft_putendl_fd(" command not found", 2);
		exit(NON_COMMAND);
	}
	else
		return (get_path_cmd_not_find_path(node->cmd_list));
}
