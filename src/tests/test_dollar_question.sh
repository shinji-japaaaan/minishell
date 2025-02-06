#!/bin/bash

# テストケース番号
test_case=1

# テストを実行する関数
run_test() {
    echo "== テストケース $test_case: $1 =="
    eval "$2"
    echo "終了ステータス: $?"
    echo ""
    test_case=$((test_case + 1))
}

# テスト開始
echo "=== $? の動作テスト (&&, ;, || なし) ==="

# 1. 正常終了のコマンド
run_test "正常終了の確認 (echo)" "echo 'Hello, World!'"

# 2. 存在しないコマンドを実行
run_test "異常終了の確認 (存在しないコマンド)" "non_existent_command"

# 3. 成功するコマンドの終了ステータス確認 (exit 0)
run_test "明示的に0を返す" "bash -c 'exit 0'"

# 4. 失敗するコマンドの終了ステータス確認 (exit 1)
run_test "明示的に1を返す" "bash -c 'exit 1'"

# 5. サブシェル内で正常終了
run_test "サブシェル内の正常終了" "(echo 'Success')"

# 6. サブシェル内で異常終了
run_test "サブシェル内の異常終了" "(non_existent_command)"

# 7. ファイルの存在チェック (存在するファイル)
run_test "ファイルの存在確認 (成功)" "[ -e /etc/passwd ]"

# 8. ファイルの存在チェック (存在しないファイル)
run_test "ファイルの存在確認 (失敗)" "[ -e /tmp/non_existent_file ]"

# 9. 標準エラー出力をリダイレクトして実行
run_test "標準エラーリダイレクト (失敗)" "non_existent_command 2>/tmp/error_log"

# 10. 標準出力のみリダイレクトして実行
run_test "標準出力リダイレクト (成功)" "echo 'Success' > /tmp/success_log"

# 11. バックグラウンドジョブを実行
run_test "バックグラウンドプロセス (成功)" "sleep 1 & wait $!"

# 12. バックグラウンドジョブで失敗
run_test "バックグラウンドプロセス (失敗)" "non_existent_command & wait $!"

# 15. トラップを使ったシグナル処理 (成功)
run_test "trapでシグナル処理 (成功)" "trap 'echo Trapped' SIGINT; kill -SIGINT $$"

# 16. トラップを使ったシグナル処理 (失敗)
run_test "trapでシグナル処理 (失敗)" "trap 'echo Trapped' SIGINT; non_existent_command"

# 17. 変数の参照と終了ステータス確認
run_test "変数参照前の $? の確認" "var=1; echo \$var"

# 18. 空の変数の参照と終了ステータス確認
run_test "空の変数参照の $? の確認" "empty_var=''; echo \$empty_var"

# 19. スクリプト内での終了ステータス確認
run_test "スクリプト内での終了ステータス確認" "bash -c 'echo Hello; exit 0'"

# 20. 他の終了ステータスが反映されない場合
run_test "終了ステータスが反映されない場合" "echo 'Hello'; echo 'Goodbye'"

# 21. 複雑なサブシェル内のコマンド実行
run_test "サブシェル内での複雑なコマンド実行 (成功)" "(echo 'Test' && echo 'Pass')"

# 22. 複雑なサブシェル内でのコマンド実行 (失敗)
run_test "サブシェル内での複雑なコマンド実行 (失敗)" "(non_existent_command && echo 'Fail')"

echo "=== テスト完了 ==="
