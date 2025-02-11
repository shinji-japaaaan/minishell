/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:53:43 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 21:48:58 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parser.h"

int		handle_internal_commands(t_cmd_invoke *parsed_list, char ***env);
bool	is_internal_commands(char *command);

int		change_directory(char *path, char **args, char ***env);
void	exit_shell(char **args);
void	echo_command(char **args);
int		print_working_directory(void);
void	print_environment(char **env);
int		export_variable(char ***env, char *args);
int		unset_variable(char ***env, char *args);
void	execute_command(t_linked_list *parsed_list);
int		handle_internal_commands(t_cmd_invoke *parsed_list, char ***env);
bool	is_internal_commands(char *command);

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

int		update_pwd_env_var(char ***env, const char *new_pwd);
char	*resolve_path(char *path, char ***env);
int		print_error(const char *msg);
char	*ft_strcat(char *dest, const char *src);

#endif
