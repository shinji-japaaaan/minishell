// File: main.c
/* ************************************************************************** */

#include "../../include/parser.h"

void run_test(const char *test_name, char *input)
{
    t_linked_list *head;

    printf("==== %s ====\n", test_name);
    printf("Input: \"%s\"\n", input);

    // パーサーを実行
    head = parser(input);

    // リンクリストの内容とトークンタイプを表示
    linked_list_print_with_token(head);

    // メモリ解放
    linked_list_free(head);
    // ※適切なメモリ解放関数を実装して使用してください。
}

int main(void)
{
    // テストケース
    run_test("Test 1: Basic command with pipe", "ls | grep \"file\" | wc -l");
    run_test("Test 2: Redirection", "cat input.txt > output.txt");
    run_test("Test 3: Double quotes and variables", "echo \"User: $USER\"");
    run_test("Test 4: Single quotes (no expansion)", "echo '$USER is not expanded here'");
    run_test("Test 5: Complex command", "echo \"The file is $FILE\" && rm -f $FILE");
    run_test("Test 6: Multiple spaces and tabs", "    echo    \"Hello\"   | cat -e\t");
    run_test("Test 7: No variables", "ls -la");
    run_test("Test 8: Empty string", "");

    return 0;
}
