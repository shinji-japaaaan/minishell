/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 07:44:28 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/12 07:46:58 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// コマンド実行関数
int execute_command(char *command) {
    pid_t pid;
    int status;

    pid = fork(); // 子プロセス作成
    if (pid == -1) {
        perror("fork");
        return 1; // エラーの場合は非ゼロの終了ステータス
    } else if (pid == 0) {
        // 子プロセスでコマンドを実行
        char *argv[] = {"/bin/sh", "-c", command, NULL};
        if (execve("/bin/sh", argv, NULL) == -1) {
            perror("execve");
            exit(1); // 子プロセスが失敗した場合
        }
    } else {
        // 親プロセスで子プロセスの終了を待つ
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status); // 終了ステータスを返す
        } else {
            return 1; // 異常終了の場合
        }
    }
    return 0;
}

// 条件付きコマンド実行関数
void conditional_execute(char *command1, char *operator, char *command2) {
    int status;

    // 最初のコマンドを実行
    status = execute_command(command1);

    if (strcmp(operator, "&&") == 0) {
        if (status == 0) {
            // command1 が成功した場合に command2 を実行
            execute_command(command2);
        }
    } else if (strcmp(operator, "||") == 0) {
        if (status != 0) {
            // command1 が失敗した場合に command2 を実行
            execute_command(command2);
        }
    }
}

int main() {
    char command1[] = "echo Hello";
    char command2[] = "ls -l";
    char operator[] = "||"; // "&&" または "||"

    conditional_execute(command1, operator, command2);

    return 0;
}
