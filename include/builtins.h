/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:53:43 by karai             #+#    #+#             */
/*   Updated: 2025/02/24 00:13:45 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "history.h"
# include "parser.h"

int		handle_internal_commands(t_cmd_invoke *parsed_list, char ***env);
bool	is_internal_commands(char *command);

int		change_directory(char *path, char **args, char ***env);
void	exit_shell(char **args, int exit_code);
bool	is_within_long(char *np);
void	echo_command(char **args);
bool	is_echo_option(char *str);
int		print_working_directory(void);
void	print_environment(char **env);
int		export_variable(char ***env, char *args);
int		unset_variable(char ***env, char *args);
void	execute_command(t_linked_list *parsed_list);
bool	is_internal_commands(char *command);

int		print_and_return(char **env);
int		is_valid_identifier(const char *arg);
int		handle_invalid_identifier(char *arg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		handle_existing_variable(char ***env, char *arg, int i);
int		add_new_variable(char ***env, char *arg, int i);
void	*ft_realloc(void *ptr, size_t new_size, size_t old_size);
int		is_numeric(char *str);
void	put_str(int fd, char *str);
void	free_env(char **env);

int		update_pwd_env_var(char ***env, const char *new_pwd);
char	*resolve_path(char *path, char ***env);
int		print_error(const char *msg);
char	*ft_strcat(char *dest, const char *src);

// builtins4_exit.c
void	exit_parent(t_cmd_invoke *parsed_list, int *last_status, char ***env,
			t_History *history);
void	exit_child(t_cmd_invoke *parsed_list, t_cmd_invoke *temp_ptr,
			char ***env, int last_status);
void	free_in_exitcmd(t_cmd_invoke *parsed_list, char ***env,
			t_History *history, bool is_parent);

#endif
