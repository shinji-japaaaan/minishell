/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 06:54:57 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/12 07:07:28 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// ファイルリダイレクトの処理関数
void handle_redirect(int redirect_type, char *file) {
    int fd;

    if (redirect_type == 1) { // '>' (出力リダイレクト)
        fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Error opening file for output");
            exit(EXIT_FAILURE);
        }
        // 標準出力をリダイレクト
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("Error redirecting output");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd); // ファイルディスクリプタを閉じる
    } else if (redirect_type == 2) { // '<' (入力リダイレクト)
        fd = open(file, O_RDONLY);
        if (fd == -1) {
            perror("Error opening file for input");
            exit(EXIT_FAILURE);
        }
        // 標準入力をリダイレクト
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("Error redirecting input");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd); // ファイルディスクリプタを閉じる
    }
}

int main() {
    // テスト用ファイル
    char *output_file = "test_output.txt";
    char *input_file = "test_input.txt";

    // 標準出力を保存
    int stdout_backup = dup(STDOUT_FILENO);
    if (stdout_backup == -1) {
        perror("Error saving STDOUT");
        return EXIT_FAILURE;
    }

    // **1. 出力リダイレクトテスト**
    printf("Testing output redirection...\n");
    handle_redirect(1, output_file); // '>' のリダイレクト
    printf("This text should be written to %s\n", output_file);
    // 標準出力を元に戻す
    if (dup2(stdout_backup, STDOUT_FILENO) == -1) {
        perror("Error restoring STDOUT");
        return EXIT_FAILURE;
    }
    close(stdout_backup);

    // **2. 入力リダイレクトテスト**
    printf("Testing input redirection...\n");
    handle_redirect(2, input_file); // '<' のリダイレクト
    char buffer[128];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("Read from %s: %s", input_file, buffer);
    } else {
        perror("Error reading from input file");
    }

    return 0;
}