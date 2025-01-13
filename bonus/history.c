/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:12:05 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/13 10:23:47 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 履歴リストを初期化
History *init_history(int max_size) {
    History *history = malloc(sizeof(History));
    if (!history) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    history->entries = malloc(max_size * sizeof(char *));
    if (!history->entries) {
        free(history);
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    history->count = 0;
    history->max_size = max_size;
    return history;
}

// 履歴リストに新しいエントリを追加
void add_to_history(History *history, const char *line) {
    if (history->count == history->max_size) {
        free(history->entries[0]);
        for (int i = 0; i < history->count - 1; i++) {
            history->entries[i] = history->entries[i + 1];
        }
        history->count--;
    }
    history->entries[history->count++] = strdup(line);
}

// 履歴をファイルに保存
void save_history_to_file(const char *filename, History *history) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }

    for (int i = 0; i < history->count; i++) {
        write(fd, history->entries[i], strlen(history->entries[i]));
        write(fd, "\n", 1);
    }

    close(fd);
}

// ファイルから履歴を読み込み
void load_history_from_file(const char *filename, History *history) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        return; // ファイルが存在しない場合はスキップ
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes;
    char *line;

    while ((bytes = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes] = '\0';
        line = strtok(buffer, "\n");
        while (line) {
            add_to_history(history, line);
            add_history(line); // readlineの履歴にも追加
            line = strtok(NULL, "\n");
        }
    }

    close(fd);
}

// 履歴の解放
void free_history(History *history) {
    for (int i = 0; i < history->count; i++) {
        free(history->entries[i]);
    }
    free(history->entries);
    free(history);
}
