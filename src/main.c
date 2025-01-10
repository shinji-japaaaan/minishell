#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) {
    char *input;

    while (1) {
        // プロンプトを表示してユーザー入力を取得
        input = readline("minishell> ");

        // 入力がNULL（EOF）なら終了
        if (!input) {
            printf("exit\n");
            break;
        }

        // 空の入力を無視する
        if (*input) {
            add_history(input);  // 入力を履歴に追加
            printf("You entered: %s\n", input);  // 入力内容を表示（処理の代わり）
        }

        free(input);  // readlineで確保したメモリを解放
    }

    return 0;
}
