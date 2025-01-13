/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:40:24 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/13 14:17:41 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// 環境変数をコピーする関数
char **copy_environment(char **envp) {
    int i = 0;
    while (envp[i]) i++;

    char **copy = malloc((i + 1) * sizeof(char *));
    if (!copy) {
        perror("malloc failed");
        exit(1);
    }

    for (i = 0; envp[i]; i++) {
        copy[i] = strdup(envp[i]);
        if (!copy[i]) {
            perror("strdup failed");
            while (--i >= 0) free(copy[i]);
            free(copy);
            exit(1);
        }
    }
    copy[i] = NULL;
    return copy;
}

// 環境変数を解放する関数
void free_environment(char **env) {
    for (int i = 0; env[i]; i++) {
        free(env[i]);
    }
    free(env);
}

void change_directory(char *path) {
    if (!path || strcmp(path, "~") == 0) {
        path = getenv("HOME");
        if (!path) {
            write(STDERR_FILENO, "cd failed: HOME not set\n", 24);
            return;
        }
    }
    if (chdir(path) == -1) {
        perror("cd failed");
    }
}

void exit_shell(char **env) {
    printf("Exiting shell...\n");
    free_environment(env); // 環境変数の解放
    exit(0);
}

void echo_command(char *args) {
    if (args) {
        printf("%s\n", args);
    } else {
        printf("\n");
    }
}

void print_working_directory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd failed");
    }
}

void print_environment(char **env) {
    for (char **env_ptr = env; *env_ptr; ++env_ptr) {
        printf("%s\n", *env_ptr);
    }
}

void export_variable(char ***env, char *arg) {
    if (!arg || !strchr(arg, '=')) {
        fprintf(stderr, "export: invalid argument\n");
        return;
    }

    int i = 0;
    for (; (*env)[i]; i++) {
        if (strncmp((*env)[i], arg, strchr(arg, '=') - arg) == 0) {
            free((*env)[i]);
            (*env)[i] = strdup(arg);
            if (!(*env)[i]) {
                perror("strdup failed");
                exit(1);
            }
            return;
        }
    }

    // 新しい変数を追加
    char **new_env = realloc(*env, (i + 2) * sizeof(char *));
    if (!new_env) {
        perror("realloc failed");
        exit(1);
    }

    new_env[i] = strdup(arg);
    if (!new_env[i]) {
        perror("strdup failed");
        exit(1);
    }
    new_env[i + 1] = NULL;
    *env = new_env;
}

void unset_variable(char ***env, char *arg) {
    int i = 0, j = 0;

    for (; (*env)[i]; i++) {
        if (strncmp((*env)[i], arg, strlen(arg)) == 0 && (*env)[i][strlen(arg)] == '=') {
            free((*env)[i]);
        } else {
            (*env)[j++] = (*env)[i];
        }
    }
    (*env)[j] = NULL;
}

int main(int argc, char **argv, char **envp) {
    char **environment = copy_environment(envp);
    char input[256];

    while (1) {
        printf("minishell> ");
        fgets(input, 256, stdin);
        input[strcspn(input, "\n")] = '\0'; // 改行を除去

        if (strcmp(input, "cd") == 0) {
            // 引数がない場合はホームディレクトリに移動
            change_directory(NULL);
        } else if (strncmp(input, "cd ", 3) == 0) {
            // 引数がある場合は指定されたパスに移動
            change_directory(input + 3);
        } else if (strcmp(input, "exit") == 0) {
            exit_shell(environment);
        } else if (strncmp(input, "echo ", 5) == 0) {
            echo_command(input + 5);
        } else if (strcmp(input, "pwd") == 0) {
            print_working_directory();
        } else if (strcmp(input, "env") == 0) {
            print_environment(environment);
        } else if (strncmp(input, "export ", 7) == 0) {
            export_variable(&environment, input + 7);
        } else if (strncmp(input, "unset ", 6) == 0) {
            unset_variable(&environment, input + 6);
        } else {
            printf("Unsupported command: %s\n", input);
        }
    }

    free_environment(environment);
    return 0;
}





