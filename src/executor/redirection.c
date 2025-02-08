/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 06:54:57 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/08 18:27:27 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_redirect(t_cmd_invoke *node, bool is_parent)
{
	int			status;
	t_redirect	*temp_ptr;

	temp_ptr = node->redirect_head->next;
	while (temp_ptr)
	{
		status = handle_redirect(temp_ptr->token_type, temp_ptr, is_parent);
		if (status != 0)
			return (status);
		temp_ptr = temp_ptr->next;
	}
	return (0);
}

void	reset_redirect_out(t_redirect *node)
{
	struct stat	st;

	if (dup2(node->stdio_backup, STDOUT_FILENO) == -1)
	{
		perror("Error restoring STDOUT");
		exit(EXIT_FAILURE);
	}
	if (fstat(node->stdio_backup, &st) == 0)
		close(node->stdio_backup);
}

void	reset_redirect_in(t_redirect *node)
{
	struct stat	st;

	if (dup2(node->stdio_backup, STDIN_FILENO) == -1)
	{
		perror("Error restoring STDIN");
		exit(EXIT_FAILURE);
	}
	if (node->token_type == TYPE_HEREDOC)
	{
		if (fstat(node->fd, &st) == 0)
			close(node->fd);
	}
	if (fstat(node->stdio_backup, &st) == 0)
		close(node->stdio_backup);
}

void	reset_redirect_recursive(t_redirect *node)
{
	if (node->token_type == TYPE_REDIRECT_OUT
		|| node->token_type == TYPE_REDIRECT_APPEND)
	{
		if (node->next == NULL)
			return (reset_redirect_out(node));
		else
		{
			reset_redirect_recursive(node->next);
			reset_redirect_out(node);
			return ;
		}
	}
	else
	{
		if (node->next == NULL)
			return (reset_redirect_in(node));
		else
		{
			reset_redirect_recursive(node->next);
			reset_redirect_in(node);
			return ;
		}
	}
}

void	reset_redirect(t_cmd_invoke *node)
{
	t_redirect	*redirect_head;

	redirect_head = node->redirect_head;
	if (redirect_head->next != NULL)
	{
		reset_redirect_recursive(redirect_head->next);
	}
}

// int	handle_redirect(TokenType token_type, t_redirect *node)
// {
// 	int	fd;

// 	if (token_type == TYPE_REDIRECT_OUT)
// 	{ // '>' の場合
// 		node->stdio_backup = dup(STDOUT_FILENO);
// 		if (node->stdio_backup == -1)
// 		{
// 			perror("Error saving STDOUT");
// 			return (EXIT_FAILURE);
// 		}
// 		fd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 		if (fd == -1)
// 		{
// 			perror("Error opening file for output");
// 			return (EXIT_FAILURE);
// 		}
// 		if (dup2(fd, STDOUT_FILENO) == -1)
// 		{
// 			perror("Error redirecting output");
// 			close(fd);
// 			return (EXIT_FAILURE);
// 		}
// 		if (close(fd) == -1)
// 		{
// 			perror("Error close");
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	else if (token_type == TYPE_REDIRECT_APPEND)
// 	{ // '>>' の場合
// 		node->stdio_backup = dup(STDOUT_FILENO);
// 		if (node->stdio_backup == -1)
// 		{
// 			perror("Error saving STDOUT");
// 			return (EXIT_FAILURE);
// 		}
// 		fd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 		if (fd == -1)
// 		{
// 			perror("Error opening file for output");
// 			return (EXIT_FAILURE);
// 		}
// 		if (dup2(fd, STDOUT_FILENO) == -1)
// 		{
// 			perror("Error redirecting output");
// 			close(fd);
// 			return (EXIT_FAILURE);
// 		}
// 		if (close(fd) == -1)
// 		{
// 			perror("Error close");
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	else if (token_type == TYPE_REDIRECT_IN)
// 	{ // '<' の場合
// 		node->stdio_backup = dup(STDIN_FILENO);
// 		if (node->stdio_backup == -1)
// 		{
// 			perror("Error saving STDIN");
// 			return (EXIT_FAILURE);
// 		}
// 		fd = open(node->filename, O_RDONLY); // 読み込み専用でファイルを開く
// 		if (fd == -1)
// 		{
// 			perror("Error opening file for input");
// 			return (EXIT_FAILURE);
// 		}
// 		if (dup2(fd, STDIN_FILENO) == -1)
// 		{
// 			perror("Error redirecting input");
// 			close(fd);
// 			return (EXIT_FAILURE);
// 		}
// 		if (close(fd) == -1)
// 		{
// 			perror("Error close");
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	else if (token_type == TYPE_HEREDOC)
// 	{
// 		node->stdio_backup = dup(STDIN_FILENO);
// 		if (node->stdio_backup == -1)
// 		{
// 			perror("Error saving STDIN");
// 			return (EXIT_FAILURE);
// 		}
// 		if (dup2(node->fd, STDIN_FILENO) == -1)
// 		{
// 			perror("Error heredoc input");
// 			close(node->fd);
// 			return (EXIT_FAILURE);
// 		}
// 		if (close(node->fd) == -1)
// 		{
// 			perror("Error close");
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	return (0);
// }

// void	reset_redirect(t_cmd_invoke *node, bool is_parent)
// {
// 	t_redirect	*redirect_in_head;
// 	t_redirect	*redirect_out_head;
// 	t_redirect	*temp_ptr;

// 	// char		buffer[1000];
// 	redirect_in_head = node->redirect_in_head;
// 	redirect_out_head = node->redirect_out_head;
// 	// 標準出力を元に戻す
// 	temp_ptr = redirect_out_head->next;
// 	while (temp_ptr)
// 	{
// 		if (is_parent == false)
// 			temp_ptr->stdio_backup = dup(STDOUT_FILENO);
// 		if (dup2(temp_ptr->stdio_backup, STDOUT_FILENO) == -1)
// 		{
// 			perror("Error restoring STDOUT");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(temp_ptr->stdio_backup);
// 		temp_ptr = temp_ptr->next;
// 	}
// 	temp_ptr = redirect_in_head->next;
// 	while (temp_ptr)
// 	{
// 		if (is_parent == false)
// 			temp_ptr->stdio_backup = dup(STDIN_FILENO);
// 		if (dup2(temp_ptr->stdio_backup, STDIN_FILENO) == -1)
// 		{
// 			perror("Error restoring STDIN");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (temp_ptr->token_type == TYPE_HEREDOC)
// 		{
// 			close(temp_ptr->fd);
// 		}
// 		close(temp_ptr->stdio_backup);
// 		temp_ptr = temp_ptr->next;
// 	}
// }

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
