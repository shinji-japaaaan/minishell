#ifndef INTERNAL_COMMANDS_H
# define INTERNAL_COMMANDS_H

# include "parser.h"

// 内部コマンドで使用する関数群の宣言
int     change_directory(char *path, char **args);
void    exit_shell(char **args);
void	echo_command(char **args);
int     print_working_directory(void);
void	print_environment(char **env);
int 	export_variable(char ***env, char *args);
int 	unset_variable(char ***env, char *args);
void	execute_command(t_linked_list *parsed_list);
int		handle_internal_commands(t_cmd_invoke *parsed_list, char ***env);
bool	is_internal_commands(char *command);

#endif
