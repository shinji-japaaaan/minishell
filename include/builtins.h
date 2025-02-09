/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:53:43 by karai             #+#    #+#             */
/*   Updated: 2025/02/09 22:26:47 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parser.h"

int		handle_internal_commands(t_cmd_invoke *parsed_list, char ***env);
bool	is_internal_commands(char *command);

// 内部コマンドで使用する関数群の宣言
int		change_directory(char *path, char **args, char **env);
void	exit_shell(char **args);
void	echo_command(char **args);
int		print_working_directory(void);
void	print_environment(char **env);
int		export_variable(char ***env, char *args);
int		unset_variable(char ***env, char *args);
void	execute_command(t_linked_list *parsed_list);
int		handle_internal_commands(t_cmd_invoke *parsed_list, char ***env);
bool	is_internal_commands(char *command);

// builtin_utils.c
int		print_and_return(char **env);
int		is_valid_identifier(const char *arg);
int		handle_invalid_identifier(char *arg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		handle_existing_variable(char ***env, char *arg, int i);
int		add_new_variable(char ***env, char *arg, int i);
void	*ft_realloc(void *ptr, size_t size);
int		is_numeric(char *str);
void	put_str(int fd, char *str);
void	free_env(char **env);

#endif
