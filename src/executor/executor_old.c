/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:33:42 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/18 20:26:12 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// フルパス解決関数の例
char *resolve_path(const char *command) {
    if (access(command, X_OK) == 0) {
        return strdup(command);
    }
    char *path_env = getenv("PATH");
    if (!path_env) {
        return NULL;
    }
    char *paths = strdup(path_env);
    char *token = strtok(paths, ":");
    while (token) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
        if (access(full_path, X_OK) == 0) {
            free(paths);
            return strdup(full_path);
        }
        token = strtok(NULL, ":");
    }
    free(paths);
    return NULL;
}

int linked_list_size(t_linked_list *head) {
    int count = 0;

    // リストを順番にたどってノードを数える
    while (head != NULL) {
        count++;
        head = head->next;
    }

    return count;
}

char **convert_list_to_array(t_linked_list *list) {
    // リンクリストのサイズを計算
    size_t size = linked_list_size(list);
    
    // 配列を確保（+1 は NULL 終端用）
    char **array = malloc((size + 1) * sizeof(char *));
    if (!array) {
        perror("malloc failed");
        exit(1);
    }

    // リンクリストの内容を配列にコピー
    size_t i = 0;
    while (list) {
        array[i++] = strdup(list->content); // 各要素をコピー
        list = list->next;
    }
    array[i] = NULL; // 配列の終端を NULL に設定
    
    return array;
}

void execute_command(t_linked_list *parsed_list) {
    pid_t pid;
    char **args;

    // リンクリストを配列に変換
    args = convert_list_to_array(parsed_list);
    if (!args || !args[0]) { // 配列が空の場合のエラーハンドリング
        fprintf(stderr, "Error: Command is empty or invalid.\n");
        return;
    }
    char *command_path = resolve_path(args[0]);
    printf("%s", args[0]);
    if (!command_path) {
        fprintf(stderr, "Error: Command not found: %s\n", args[0]);
        return;
    }
    // args[0] にフルパスを設定
    free(args[0]);  // 元の値を解放
    args[0] = command_path;
    pid = fork(); // プロセスを分岐
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // 子プロセスでexecveを呼び出す
        if (execve(args[0], args, NULL) == -1) {
            perror("execve failed");
            exit(1);
        }
    } else {
        // 親プロセスは子プロセスの終了を待つ
        wait(NULL);
    }

    // メモリ解放
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}

// int main() {
//     char command[256] = "ls -l"; // 仮の入力
//     execute_command(command);
//     return 0;
// }
