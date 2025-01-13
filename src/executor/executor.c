/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:33:42 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/13 14:18:30 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void execute_command(char *input) {
    pid_t pid;
    char *args[3]; // コマンドと引数、最後はNULLで終わる必要がある
    args[0] = "/bin/ls"; // 実行するプログラムのパス
    args[1] = "-l";      // 引数
    args[2] = NULL;      // 終端

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
}

int main() {
    char command[256] = "ls -l"; // 仮の入力
    execute_command(command);
    return 0;
}
