/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:40:24 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/11 11:07:19 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void change_directory(char *path) {
    if (strcmp(path, "~") == 0) {
        // "~"が指定された場合はHOMEディレクトリに変更
        char *home = getenv("HOME");
        if (home != NULL) {
            if (chdir(home) == -1) {
                perror("cd failed");
            } else {
                char cwd[256];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    printf("Current directory: %s\n", cwd);
                } else {
                    perror("getcwd failed");
                }
            }
        } else {
            perror("HOME environment variable is not set");
        }
    } else {
        // 他のディレクトリに移動
        if (chdir(path) == -1) {
            perror("cd failed");
        } else {
            char cwd[256];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Current directory: %s\n", cwd);
            } else {
                perror("getcwd failed");
            }
        }
    }
}

void exit_shell() {
    printf("Exiting shell...\n");
    exit(0);
}

int main() {
    char input[256];

    while (1) {
        printf("minishell> ");
        fgets(input, 256, stdin);
        input[strcspn(input, "\n")] = '\0'; // 改行を除去

        if (strncmp(input, "cd ", 3) == 0) {
            change_directory(input + 3); // "cd "の後のパスを渡す
        } else if (strcmp(input, "exit") == 0) {
            exit_shell();
        } else {
            printf("Unsupported command: %s\n", input);
        }
    }

    return 0;
}



