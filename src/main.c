/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 07:28:26 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/11 07:42:27 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define HISTORY_FILE ".minishell_history"

void save_history_to_file(const char *filename) {
    printf("Saving history to: %s\n", filename);
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }

    HIST_ENTRY *entry;
    for (int i = 0; (entry = history_get(i + history_base)); i++) {
        write(fd, entry->line, strlen(entry->line));
        write(fd, "\n", 1);
    }

    close(fd);
}

void load_history_from_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    char buffer[1024];
    ssize_t bytes;
    char *line;

    while ((bytes = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes] = '\0';  // 読み込んだデータの末尾に終端文字を追加
        line = strtok(buffer, "\n");
        while (line) {
            add_history(line);
            line = strtok(NULL, "\n");
        }
    }

    close(fd);
}

int main(void) {
    char *input;

    // 履歴ファイルの読み込み
    load_history_from_file(HISTORY_FILE);

    while (1) {
        input = readline("minishell> ");
        if (!input) {
            printf("exit\n");
            break;
        }

        if (*input) {
            add_history(input);
        }

        printf("You entered: %s\n", input);
        free(input);
    }

    // 履歴を保存
    save_history_to_file(HISTORY_FILE);

    rl_clear_history();
    return 0;
}

