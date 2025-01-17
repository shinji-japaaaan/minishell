/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 06:54:57 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/13 15:41:56 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_redirect(int redirect_type, char *file) {
    int fd;

    if (redirect_type == 1) { // '>' の場合
        fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Error opening file for output");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("Error redirecting output");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
    } else if (redirect_type == 2) { // '<' の場合
        fd = open(file, O_RDONLY); // 読み込み専用でファイルを開く
        if (fd == -1) {
            perror("Error opening file for input");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("Error redirecting input");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
    }
}

int main() {
    char *output_file = "test_output.txt";
    char *input_file = "test_input.txt";
    char buffer[128];
    ssize_t bytes_read;

    // 標準出力を保存
    int stdout_backup = dup(STDOUT_FILENO);
    if (stdout_backup == -1) {
        perror("Error saving STDOUT");
        return EXIT_FAILURE;
    }

    // 出力リダイレクトのテスト
    printf("Testing output redirection...\n");
    handle_redirect(1, output_file); // '>' のリダイレクト
    printf("This text should be written to %s\n", output_file);

    // 標準出力を元に戻す
    if (dup2(stdout_backup, STDOUT_FILENO) == -1) {
        perror("Error restoring STDOUT");
        return EXIT_FAILURE;
    }
    close(stdout_backup);

    // 標準入力を保存
    int stdin_backup = dup(STDIN_FILENO);
    if (stdin_backup == -1) {
        perror("Error saving STDIN");
        return EXIT_FAILURE;
    }

    // 入力リダイレクトのテスト
    printf("Testing input redirection...\n");
    handle_redirect(2, input_file); // '<' のリダイレクト

    // ファイルをバッファサイズずつ繰り返し読み込む
    printf("Reading from input file:\n");
    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0'; // Null文字で終端
        printf("%s", buffer);      // 標準出力に出力
    }

    if (bytes_read == -1) { // エラー処理
        perror("Error reading from input file");
        return EXIT_FAILURE;
    }

    // 標準入力を元に戻す
    if (dup2(stdin_backup, STDIN_FILENO) == -1) {
        perror("Error restoring STDIN");
        return EXIT_FAILURE;
    }
    close(stdin_backup);

    return EXIT_SUCCESS;
}

