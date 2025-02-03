/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 07:59:43 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/03 22:22:17 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	global_pid = 0;

int handle_internal_commands(t_cmd_invoke *parsed_list, char ***env) {
    char *command = parsed_list->cmd_list[0];
    char **args = parsed_list->cmd_list;

    if (strcmp(command, "cd") == 0) {
        if (args[1] && args[2]) {
            write(STDERR_FILENO, "cd: too many arguments\n", 23);
            return 1;  // Bash では exit code 1
        }
        if (args[1] == NULL || strcmp(args[1], "$PWD") == 0) {
            return change_directory(getenv("PWD"));
        }
        return change_directory(args[1]);
    } else if (strcmp(command, "exit") == 0) {
        exit_shell(args); // exit コマンド処理を exit_shell に委譲
        return 1; // 実際にはここには到達しないが、必須の return
    } else if (strcmp(command, "echo") == 0) {
        return (echo_command(args), 0);
    } else if (strcmp(command, "pwd") == 0) {
        return (print_working_directory());
    } else if (strcmp(command, "env") == 0) {
        return (print_environment(*env), 1);
    } else if (strcmp(command, "export") == 0) {
        return export_variable(env, args[1]);
    } else if (strcmp(command, "unset") == 0) {
        if (args[1] == NULL) {
            return 0;
        }
        return (unset_variable(env, args[1]));
    } else {
        return 0;
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

void	handle_sigint(int signum)
{
	(void)signum; // 未使用変数を無視
	if (global_pid != 0)
	{
		kill(global_pid, SIGINT);
	}
	else
	{
		write(STDOUT_FILENO, "\n", 1); // 改行のみ表示
		rl_replace_line("", 0);        // 入力行をクリア
		rl_on_new_line();              // 新しい行に移動
		rl_redisplay();                // プロンプトを再表示
	}
}

// 端末のエコー制御（ECHOCTL を無効化して `^\` を表示しないようにする）
void disable_echoctl(void)
{
    struct termios term;

    if (!isatty(STDIN_FILENO))
    {
        return; // 端末でない場合は設定変更をスキップ
    }
    if (tcgetattr(STDIN_FILENO, &term) == -1)
    {
        perror("tcgetattr");
        return; // 端末でない場合はエラーを無視
    }
    term.c_lflag &= ~ECHOCTL; // ECHOCTL を無効化 (`^\` を表示しない)
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
    {
        perror("tcsetattr");
    }
}

void setup_signal_handler(void)
{
    struct sigaction sa;

    // SIGINT に対するハンドラ設定
    sa.sa_handler = handle_sigint;
    sa.sa_flags = SA_RESTART; // システムコールを中断させない
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    // SIGQUIT (ctrl-\) を無視する設定
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    // `^\` を表示しないように端末設定を変更
    if (isatty(STDIN_FILENO))
    {
        disable_echoctl();
    }
}

// シェル処理関数
void	process_shell(char ***env)
{
	char			*input;
	t_cmd_invoke	*parsed_list;
	History			*history;
	int				last_status;
	char			*command;

	// シグナルハンドラの設定
	setup_signal_handler();
	last_status = 0;
	// 履歴リストの初期化
	history = init_history(MAX_HISTORY);
	// 履歴ファイルの読み込み
	load_history_from_file(HISTORY_FILE, history);
	while (1)
	{
		global_pid = 0;
		// プロンプト表示と入力受付
		input = readline("minishell> ");
		if (!input)
		{ // EOFやエラー時の終了処理
			break ;
		}
		if (*input == '\0')
		{
			free(input); // 空入力時もメモリ解放
			continue ;
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
		// コマンド部分
		command = parsed_list->next->cmd_list[0];
		// 内部コマンドの処理を外だし関数で呼び出す
		if (is_internal_commands(command) && parsed_list->next->next == NULL)
		{
			last_status = heredoc_redirect_list(parsed_list->next->redirect_head);
			// printf("last status %d\n", last_status);
			if (!last_status)
			{
				last_status = open_redirect(parsed_list->next, true);
				if (last_status == 0)
					last_status = handle_internal_commands(parsed_list->next,
							env);
				reset_redirect(parsed_list->next);
			}
			else
				heredoc_close(parsed_list->next);
		}
		else
			// 外部コマンドの処理
			last_status = cmd_execute_main(parsed_list);
		// メモリ解放
		free_all(&parsed_list);
		free(input); // 動的メモリの解放
	}
	// 履歴を保存
	save_history_to_file(HISTORY_FILE, history);
	// メモリ解放
	free_history(history);
	rl_clear_history();
}

char **duplicate_env(char **envp) {
    int count = 0;
    while (envp[count]) count++;

    char **env = malloc((count + 1) * sizeof(char *));
    if (!env) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        env[i] = strdup(envp[i]);  // 環境変数をコピー
        if (!env[i]) {
            perror("strdup failed");
            exit(EXIT_FAILURE);
        }
    }
    env[count] = NULL;  // NULL 終端を追加
    return env;
}

void free_env(char **env) {
    if (!env) {
        return;  // NULL チェック
    }

    for (int i = 0; env[i]; i++) {
        free(env[i]);  // 各環境変数のメモリを解放
    }
    free(env);  // 環境変数リスト自体のメモリを解放
}


int	main(int argc, char **argv, char **envp)
{
	(void)argc;          // argc を無視
	(void)argv;          // argv を無視

	char **env = duplicate_env(envp);  // `envp` をコピーする
	process_shell(&env); // 入力受付関数を呼び出し
	free_env(env);  // 環境変数のメモリを解放
	return (0);
}
