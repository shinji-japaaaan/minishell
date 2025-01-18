/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 07:59:43 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/18 07:42:47 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

// シェルの処理全体を管理する関数
void process_shell(void) {
    char *input;
    t_linked_list *parsed_list;

    // 履歴リストの初期化
    History *history = init_history(MAX_HISTORY);

    // 履歴ファイルの読み込み
    load_history_from_file(HISTORY_FILE, history);

    while (1) {
        // プロンプト表示と入力受付
        input = readline("minishell> ");
        if (!input) { // EOFやエラー時の終了処理
            printf("exit\n");
            break;
        }

        if (*input) { // 入力が空でない場合
            add_history(input);           // readline用の履歴に追加
            add_to_history(history, input); // 自前の履歴にも追加
        }

        // 内部コマンド "history" の処理
        if (strcmp(input, "history") == 0) {
            for (int i = 0; i < history->count; i++) {
                printf("%d: %s\n", i + 1, history->entries[i]);
            }
            free(input);
            continue; // 次の入力を待つ
        }

        // パーサーの実行
        parsed_list = parser(input);
        if (!parsed_list) {
            fprintf(stderr, "Error: Failed to parse input.\n");
            free(input);
            continue; // 次の入力を待つ
        }

        // リンクリストの内容とトークンタイプを表示
        linked_list_print_with_token(parsed_list);

        // パース後の処理をここに追加
        // 例えば、コマンド実行部分を呼び出すなど

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

int main(void) {
    process_shell(); // 入力受付関数を呼び出し
    return 0;
}


