#ifndef INTERNAL_COMMANDS_H
#define INTERNAL_COMMANDS_H

// 内部コマンドで使用する関数群の宣言
void change_directory(char *path);
void exit_shell(char **env);
void echo_command(char *args);
void print_working_directory(void);
void print_environment(char **env);
void export_variable(char ***env, char *args);
void unset_variable(char ***env, char *args);
void execute_command(t_linked_list *parsed_list);

#endif
