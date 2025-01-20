/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 06:54:57 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/21 06:29:58 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	open_redirect(t_cmd_invoke *node)
{
	handle_redirect_all(node->redirect_in_head);
	handle_redirect_all(node->redirect_out_head);
}

void	handle_redirect_all(t_redirect *head)
{
	t_redirect	*temp_ptr;

	temp_ptr = head->next;
	while (temp_ptr)
	{
		handle_redirect(temp_ptr->token_type, temp_ptr);
		temp_ptr = temp_ptr->next;
	}
}

void	handle_redirect(TokenType token_type, t_redirect *node)
{
	int	fd;

	// printf("redirect type %d\n", token_type);
	if (token_type == TYPE_REDIRECT_OUT)
	{ // '>' の場合
		node->stdio_backup = dup(STDOUT_FILENO);
		if (node->stdio_backup == -1)
		{
			perror("Error saving STDOUT");
			exit(EXIT_FAILURE);
		}
		fd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Error opening file for output");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("Error redirecting output");
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
    else if (token_type == TYPE_REDIRECT_APPEND)
	{ // '>' の場合
		node->stdio_backup = dup(STDOUT_FILENO);
		if (node->stdio_backup == -1)
		{
			perror("Error saving STDOUT");
			exit(EXIT_FAILURE);
		}
		fd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("Error opening file for output");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("Error redirecting output");
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
	else if (token_type == TYPE_REDIRECT_IN)
	{ // '<' の場合
		node->stdio_backup = dup(STDIN_FILENO);
		if (node->stdio_backup == -1)
		{
			perror("Error saving STDIN");
			exit(EXIT_FAILURE);
		}
		fd = open(node->filename, O_RDONLY); // 読み込み専用でファイルを開く
		if (fd == -1)
		{
			perror("Error opening file for input");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("Error redirecting input");
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}

void	reset_redirect(t_cmd_invoke *node)
{
	t_redirect	*redirect_in_head;
	t_redirect	*redirect_out_head;
	t_redirect	*temp_ptr;

	redirect_in_head = node->redirect_in_head;
	redirect_out_head = node->redirect_out_head;
	// 標準入力を元に戻す
	temp_ptr = redirect_in_head->next;
	while (temp_ptr)
	{
		if (dup2(temp_ptr->stdio_backup, STDIN_FILENO) == -1)
		{
			perror("Error restoring STDIN");
			exit(EXIT_FAILURE);
		}
		temp_ptr = temp_ptr->next;
	}
	// 標準出力を元に戻す
	temp_ptr = redirect_out_head->next;
	while (temp_ptr)
	{
		if (dup2(temp_ptr->stdio_backup, STDOUT_FILENO) == -1)
		{
			perror("Error restoring STDOUT");
			exit(EXIT_FAILURE);
		}
		temp_ptr = temp_ptr->next;
	}
}

// int	main(void)
// {
// 	char	*output_file;
// 	char	*input_file;
// 	char	buffer[128];
// 	ssize_t	bytes_read;
// 	int		stdout_backup;
// 	int		stdin_backup;

// 	output_file = "test_output.txt";
// 	input_file = "test_input.txt";
// 	// 標準出力を保存
// 	stdout_backup = dup(STDOUT_FILENO);
// 	if (stdout_backup == -1)
// 	{
// 		perror("Error saving STDOUT");
// 		return (EXIT_FAILURE);
// 	}
// 	// 出力リダイレクトのテスト
// 	printf("Testing output redirection...\n");
// 	handle_redirect(1, output_file); // '>' のリダイレクト
// 	printf("This text should be written to %s\n", output_file);
// 	// 標準出力を元に戻す
// 	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
// 	{
// 		perror("Error restoring STDOUT");
// 		return (EXIT_FAILURE);
// 	}
// 	close(stdout_backup);
// 	// 標準入力を保存
// 	stdin_backup = dup(STDIN_FILENO);
// 	if (stdin_backup == -1)
// 	{
// 		perror("Error saving STDIN");
// 		return (EXIT_FAILURE);
// 	}
// 	// 入力リダイレクトのテスト
// 	printf("Testing input redirection...\n");
// 	handle_redirect(2, input_file); // '<' のリダイレクト
// 	// ファイルをバッファサイズずつ繰り返し読み込む
// 	printf("Reading from input file:\n");
// 	while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1)) > 0)
// 	{
// 		buffer[bytes_read] = '\0'; // Null文字で終端
// 		printf("%s", buffer);      // 標準出力に出力
// 	}
// 	if (bytes_read == -1)
// 	{ // エラー処理
// 		perror("Error reading from input file");
// 		return (EXIT_FAILURE);
// 	}
// 	// 標準入力を元に戻す
// 	if (dup2(stdin_backup, STDIN_FILENO) == -1)
// 	{
// 		perror("Error restoring STDIN");
// 		return (EXIT_FAILURE);
// 	}
// 	close(stdin_backup);
// 	return (EXIT_SUCCESS);
// }
