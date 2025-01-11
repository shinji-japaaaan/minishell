/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:40:24 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/11 11:16:59 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ; // 環境変数へのアクセス

void change_directory(char *path) {
    if (chdir(path) == -1) {
        perror("cd failed");
    }
}

void exit_shell() {
    printf("Exiting shell...\n");
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

void print_environment() {
    for (char **env = environ; *env; ++env) {
        printf("%s\n", *env);
    }
}

void export_variable(char *arg) {
    if (!arg || !strchr(arg, '=')) {
        fprintf(stderr, "export: invalid argument\n");
        return;
    }
    if (putenv(arg) != 0) {
        perror("export failed");
    }
}

void unset_variable(char *arg) {
    if (unsetenv(arg) != 0) {
        perror("unset failed");
    }
}

int main() {
    char input[256];

    while (1) {
        printf("minishell> ");
        fgets(input, 256, stdin);
        input[strcspn(input, "\n")] = '\0'; // 改行を除去

        if (strncmp(input, "cd ", 3) == 0) {
            change_directory(input + 3);
        } else if (strcmp(input, "exit") == 0) {
            exit_shell();
        } else if (strncmp(input, "echo ", 5) == 0) {
            echo_command(input + 5);
        } else if (strcmp(input, "pwd") == 0) {
            print_working_directory();
        } else if (strcmp(input, "env") == 0) {
            print_environment();
        } else if (strncmp(input, "export ", 7) == 0) {
            export_variable(input + 7);
        } else if (strncmp(input, "unset ", 6) == 0) {
            unset_variable(input + 6);
        } else {
            printf("Unsupported command: %s\n", input);
        }
    }

    return 0;
}




