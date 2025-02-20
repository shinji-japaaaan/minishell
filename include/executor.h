/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:20:18 by karai             #+#    #+#             */
/*   Updated: 2025/02/20 21:30:01 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define NON_COMMAND 127
# define NO_PERMISSION 126

# include "history.h"

// executor.c
int				parent_process_wait(t_cmd_invoke *head);
void			close_fd_in_child(t_cmd_invoke *node);
void			cmd_execute_child(t_cmd_invoke *head, t_cmd_invoke *temp_ptr,
					bool is_first, char **env);
t_cmd_invoke	*cmd_execute_parent(t_cmd_invoke *temp_ptr, bool *is_first);
int				cmd_execute_main(t_cmd_invoke *head, char **env,
					int *last_status, t_History *history);

// executor_handle_fd.c
void			handle_command_execution(t_cmd_invoke *temp_ptr, bool is_first);
void			handle_open_redirect(t_cmd_invoke *head, t_cmd_invoke *temp_ptr,
					char **env);
t_cmd_invoke	*cmd_pipe_connect(t_cmd_invoke *temp_ptr);

// cmd_execute.c
void			cmd_execute_first(t_cmd_invoke *node);
void			cmd_execute_last(t_cmd_invoke *node);
void			cmd_execute_middle(t_cmd_invoke *node);

// cmd_execute_utils.c
void			perror_exit(char *str, char **str_array1, char **str_array2,
					int exit_status);

// free.c
void			free1dim(char **str);
void			free2dim(char ***str_array);
void			free_redirect(t_redirect **redirect_head);
void			free_cmd_node(t_cmd_invoke *node);
void			free_all(t_cmd_invoke **cmd_head);
void			free_linked_list_only_node(t_linked_list **head_list);
void			free_linked_list_all(t_linked_list **head_list);
void			fext_incmdpath(char **dir_array, t_cmd_invoke *head, char **env,
					int exit_status);

// get_path.c
char			*get_path_cmd(char *path_env, char **cmd, t_cmd_invoke *head,
					char **env);
char			*get_path_cmd_part(char **dir_array, char **cmd, size_t i);
char			*get_path_cmd_not_find_path(char **cmd, t_cmd_invoke *head,
					char **env);
char			*get_path_main(t_cmd_invoke *node, char **env,
					t_cmd_invoke *head);
void			is_directory(t_cmd_invoke *node, char **env,
					t_cmd_invoke *head);

// get_path_utils.c
int				is_access(char *full_path);
bool			is_full_relative_path(char *str);

// redirection.c
int				open_redirect(t_cmd_invoke *node, bool is_parent);
void			reset_redirect_out(t_redirect *node);
void			reset_redirect_in(t_redirect *node);
void			reset_redirect_recursive(t_redirect *node);
void			reset_redirect(t_cmd_invoke *node);

// handle_redirect.c
int				handle_redirect_out(t_redirect *node, bool is_parent);
int				handle_redirect_append(t_redirect *node, bool is_parent);
int				handle_redirect_in(t_redirect *node, bool is_parent);
int				handle_redirect_heredoc(t_redirect *node, bool is_parent);
int				handle_redirect(t_TokenType token_type, t_redirect *node,
					bool is_parent);

// hande}_redirect_parent.c
int				handle_redirect_parent(t_TokenType token_type,
					t_redirect *node);
int				open_redirect_parent(t_cmd_invoke *node);

#endif
