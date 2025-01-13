/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 06:54:57 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/13 14:18:37 by sishizaw         ###   ########.fr       */
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

    // 入力リダイレクトのテスト
    printf("Testing input redirection...\n");
    handle_redirect(2, input_file); // '<' のリダイレクト

    // read を使ってデータを読み込む
    bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("Error reading from input file");
        return EXIT_FAILURE;
    }
    buffer[bytes_read] = '\0'; // Null文字で終端
    printf("Read from %s: %s", input_file, buffer);

    return EXIT_SUCCESS;
}
