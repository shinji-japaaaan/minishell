/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 07:59:43 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/07 06:16:24 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_env(char **env) {
    if (!env) {
        return;  // NULL チェック
    }

    for (int i = 0; env[i]; i++) {
        free(env[i]);  // 各環境変数のメモリを解放
    }
    free(env);  // 環境変数リスト自体のメモリを解放
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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;          // argc を無視
	(void)argv;          // argv を無視

	char **env = duplicate_env(envp);  // `envp` をコピーする
	process_shell(&env); // 入力受付関数を呼び出し
	free_env(env);  // 環境変数のメモリを解放
	return (0);
}
