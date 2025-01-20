/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:20:18 by karai             #+#    #+#             */
/*   Updated: 2025/01/20 21:58:37 by karai            ###   ########.fr       */
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

//redirection.c
void	open_redirect(t_cmd_invoke *node);
void	handle_redirect_all(t_redirect *head);
void	handle_redirect(TokenType token_type, t_redirect *node);
void	reset_redirect(t_cmd_invoke *node);

#endif
