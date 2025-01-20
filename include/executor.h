/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipileine.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:20:18 by karai             #+#    #+#             */
/*   Updated: 2025/01/19 05:56:23 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define NON_COMMAND 127
# define NO_PERMISSION 126

// cmd_execute_main.c
int		parent_process_wait(t_cmd_invoke *head);
void	cmd_execute_first_last(t_cmd_invoke *node);
void	cmd_execute_first(t_cmd_invoke *node);
void	cmd_execute_last(t_cmd_invoke *node);
void	cmd_execute_middle(t_cmd_invoke *node);
int		cmd_execute_main(t_cmd_invoke *head);

// cmd_execute_utils.c
void	perror_exit(char *str, char **str_array1, char **str_array2,
			int exit_status);

// free.c
void	free2dim(char **str_array);

// get_path.c
char	*get_path_cmd(char *path_env, char **cmd);
char	*get_path_cmd_part(char **dir_array, char **cmd, char *tmp_str);
char	*get_path_cmd_not_find_path(char **cmd);
char	*get_path_main(t_cmd_invoke *node);

// get_path_utils.c
int		is_access(char *full_path);
bool	is_full_relative_path(char *str);

#endif
