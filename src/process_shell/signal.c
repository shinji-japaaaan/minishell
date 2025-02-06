/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 06:13:41 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/07 06:14:19 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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