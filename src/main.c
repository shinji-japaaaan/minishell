/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 07:59:43 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/13 10:23:34 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void) {
    char *input;

    // 履歴リストの初期化
    History *history = init_history(MAX_HISTORY);

    // 履歴ファイルの読み込み
    load_history_from_file(HISTORY_FILE, history);

    while (1) {
        input = readline("minishell> ");
        if (!input) {
            printf("exit\n");
            break;
        }

        if (*input) {
            add_history(input);          // readline用の履歴に追加
            add_to_history(history, input); // 自前の履歴にも追加
        }

        if (strcmp(input, "history") == 0) {
            for (int i = 0; i < history->count; i++) {
                printf("%d: %s\n", i + 1, history->entries[i]);
            }
        }
        free(input);
    }

    // 履歴を保存
    save_history_to_file(HISTORY_FILE, history);

    // メモリ解放
    free_history(history);
    rl_clear_history();
    return 0;
}

