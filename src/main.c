/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 07:59:43 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/24 21:04:44 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_redirect(t_redirect *head)
{
	t_redirect	*ptr_temp;

	ptr_temp = head->next;
	while (ptr_temp)
	{
		printf("%s\n", ptr_temp->filename);
		ptr_temp = ptr_temp->next;
	}
}

void	print_cmd(t_cmd_invoke *head)
{
	t_cmd_invoke	*ptr_temp;
	size_t			i;

	i = 0;
	ptr_temp = head->next;
	while (ptr_temp)
	{
		i = 0;
		printf("cmd\n");
		while (ptr_temp->cmd_list[i])
		{
			printf("%s\n", ptr_temp->cmd_list[i]);
			i += 1;
		}
		printf("redirect_in\n");
		print_redirect(ptr_temp->redirect_in_head);
		printf("redirect_out\n");
		print_redirect(ptr_temp->redirect_out_head);
		// printf("%p\n", ptr_temp);
		ptr_temp = ptr_temp->next;
	}
}

int	handle_internal_commands(char *command, char *args, char **env)
{
	if (strcmp(command, "cd") == 0)
	{
		return (change_directory(args), 1);
	}
	else if (strcmp(command, "exit") == 0)
	{
		return (exit_shell(env), 1);
	}
	else if (strcmp(command, "echo") == 0)
	{
		return (echo_command(args), 1);
	}
	else if (strcmp(command, "pwd") == 0)
	{
		return (print_working_directory(), 1);
	}
	else if (strcmp(command, "env") == 0)
	{
		return (print_environment(env), 1);
	}
	else if (strncmp(command, "export", 7) == 0)
	{
		return (export_variable(&env, args), 1);
	}
	else if (strncmp(command, "unset", 5) == 0)
	{
		return (unset_variable(&env, args), 1);
	}
	else
	{
		return (0);
	}
}

bool	is_internal_commands(char *command)
{
	if (strcmp(command, "cd") == 0)
		return (true);
	else if (strcmp(command, "exit") == 0)
		return (true);
	else if (strcmp(command, "echo") == 0)
		return (true);
	else if (strcmp(command, "pwd") == 0)
		return (true);
	else if (strcmp(command, "env") == 0)
		return (true);
	else if (strncmp(command, "export", 7) == 0)
		return (true);
	else if (strncmp(command, "unset", 5) == 0)
		return (true);
	else
		return (false);
}

void	process_shell(char **env)
{
	char			*input;
	t_cmd_invoke	*parsed_list;
	History			*history;
	int				last_status;
	char			*command;
	char			*args;

	last_status = 0;
	// 履歴リストの初期化
	history = init_history(MAX_HISTORY);
	// 履歴ファイルの読み込み
	load_history_from_file(HISTORY_FILE, history);
	while (1)
	{
		// プロンプト表示と入力受付
		input = readline("minishell> ");
		if (!input)
		{ // EOFやエラー時の終了処理
			printf("exit\n");
			break ;
		}
		if (*input)
		{                                   // 入力が空でない場合
			add_history(input);             // readline用の履歴に追加
			add_to_history(history, input); // 自前の履歴にも追加
		}
		// input error before parser
		if (parse_error_quote(input) || parse_error_unexpected_str(input))
		{
			ft_putendl_fd("syntax error", 2);
			free(input);
			continue ;
		}
		// パーサーの実行
		parsed_list = parser(input, last_status);
		if (!parsed_list)
		{
			fprintf(stderr, "Error: Failed to parse input.\n");
			free(input);
			continue ; // 次の入力を待つ
		}
		heredoc_main(parsed_list);
		// リストからコマンドと引数を取得
		command = parsed_list->next->cmd_list[0];
		// コマンド部分
		args = parsed_list->next ? parsed_list->next->cmd_list[1] : NULL;
		// 引数部分
		// print_cmd(parsed_list);
		// 内部コマンドの処理を外だし関数で呼び出す
		if (is_internal_commands(command) && parsed_list->next->next == NULL)
		{
			open_redirect(parsed_list->next);
			last_status = handle_internal_commands(command, args, env);
			reset_redirect(parsed_list->next);
		}
		else
			// 外部コマンドの処理
			last_status = cmd_execute_main(parsed_list);
		// メモリ解放
		linked_list_free(parsed_list);
		free(input); // 動的メモリの解放
	}
	// 履歴を保存
	save_history_to_file(HISTORY_FILE, history);
	// メモリ解放
	free_history(history);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;          // argc を無視
	(void)argv;          // argv を無視
	process_shell(envp); // 入力受付関数を呼び出し
	return (0);
}
