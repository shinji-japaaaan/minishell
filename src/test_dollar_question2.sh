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
echo "=== $? の動作テスト (無効な引数も含む) ==="

# 1. 無効な引数を与えた場合（`echo` コマンドに不正な引数）
run_test "無効な引数（`echo` の引数として過剰な数の引数）" "echo 'Hello' 'extra_argument'"

# 2. 無効な引数を与えた場合（`ls` コマンドに無効なファイルパス）
run_test "無効な引数（`ls` コマンドに存在しないファイルを指定）" "ls /non_existent_file"

# 3. 無効な引数を与えた場合（`cp` コマンドに無効なファイルパスを指定）
run_test "無効な引数（`cp` コマンドで存在しないソースファイル）" "cp /non_existent_file /tmp"

# 4. 無効な引数を与えた場合（`rm` コマンドに無効なファイルパスを指定）
run_test "無効な引数（`rm` コマンドで存在しないファイルを削除）" "rm /non_existent_file"

# 5. 無効な引数を与えた場合（`cat` コマンドに無効なファイルパスを指定）
run_test "無効な引数（`cat` コマンドで無効なファイルを読み込もうとする）" "cat /non_existent_file"

# 6. 無効な引数を与えた場合（`tar` コマンドで無効なアーカイブファイルを指定）
run_test "無効な引数（`tar` コマンドで無効なアーカイブファイルを指定）" "tar -xvf /non_existent_archive.tar"

# 7. 無効な引数を与えた場合（`touch` コマンドで無効なファイル名を指定）
run_test "無効な引数（`touch` コマンドで無効なファイル名を指定）" "touch /non_existent_dir/file.txt"

# 8. 無効な引数を与えた場合（`mkdir` コマンドで無効なディレクトリ名を指定）
run_test "無効な引数（`mkdir` コマンドで無効なディレクトリ名を指定）" "mkdir /non_existent_dir/new_directory"

# 9. 無効な引数を与えた場合（`find` コマンドで無効なパスを指定）
run_test "無効な引数（`find` コマンドで無効なパスを指定）" "find /non_existent_path -name '*.txt'"

# 10. 無効な引数を与えた場合（`ping` コマンドで無効なホストを指定）
run_test "無効な引数（`ping` コマンドで無効なホスト名を指定）" "ping non_existent_host"

echo "=== テスト完了 ==="
