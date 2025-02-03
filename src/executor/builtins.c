/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:40:24 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/03 20:02:05 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// 環境変数をコピーする関数
char **copy_environment(char **envp) {
    int i = 0;
    while (envp[i]) i++;

    char **copy = malloc((i + 1) * sizeof(char *));
    if (!copy) {
        perror("malloc failed");
        exit(1);
    }

    for (i = 0; envp[i]; i++) {
        copy[i] = strdup(envp[i]);
        if (!copy[i]) {
            perror("strdup failed");
            while (--i >= 0) free(copy[i]);
            free(copy);
            exit(1);
        }
    }
    copy[i] = NULL;
    return copy;
}

int change_directory(char *path) {
    if (!path || strcmp(path, "~") == 0) {
        path = getenv("HOME");
        if (!path) {
            write(STDERR_FILENO, "cd failed: HOME not set\n", 24);
            return 1;  // HOME が設定されていない場合は失敗として1を返す
        }
    }
    
    if (chdir(path) == -1) {
        perror("cd failed");
        return 1;  // cdが失敗した場合は1を返す
    }

    return 0;  // 成功した場合は0を返す
}

void free_environment(char **env) {
    if (!env) return;  // NULL ポインタのチェック

    for (int i = 0; env[i]; i++) {
        free(env[i]);
    }
    free(env); // env の二重解放を防ぐ
    env = NULL; // 解放後に NULL をセットしてダングリングポインタを防ぐ
}


void exit_shell(char **args) {
    if (args[1] && args[2]) {
        write(STDERR_FILENO, "exit: too many arguments\n", 25);
        exit(1); // 引数が多すぎる場合はエラーコード1
    }
    
    if (args[1]) {
        char *endptr;
        long code = strtol(args[1], &endptr, 10);

        if (*endptr != '\0') {
            write(STDERR_FILENO, "exit: numeric argument required\n", 33);
            exit(255); // 数値以外が含まれている場合
        }
        exit((int)code); // 数値が有効ならそのままexit
    }
    
    exit(0); // 引数がない場合は正常終了
}


void echo_command(char **args)
{
    if (!args || !args[0]) {
        return; // argsがNULLの場合は何もしない
    }

    int no_newline = 0;
    int i = 1; // 最初の引数はコマンド名なのでスキップ

    // '-n' オプションの判定（複数の '-n' を許可）
    while (args[i] && strncmp(args[i], "-n", 2) == 0 && strlen(args[i]) == 2) {
        no_newline = 1;
        i++; // 次の引数に進む
    }

    // 引数をスペースで区切って出力
    while (args[i]) {
        printf("%s", args[i]);
        if (args[i + 1]) {
            printf(" "); // 次の引数があればスペースを追加
        }
        i++;
    }

    // 改行の処理
    if (!no_newline) {
        printf("\n");
    }
}


int print_working_directory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        return (0);
    } else {
        perror("pwd failed");
        return (1);
    }
}

void print_environment(char **env) {
    for (char **env_ptr = env; *env_ptr; ++env_ptr) {
        printf("%s\n", *env_ptr);
    }
}

#include <stdio.h>

void print_env(char **env) {
    if (!env || !env[0]) {
        return;
    }
    for (int i = 0; env[i]; i++) {
        printf("declare -x %s\n", env[i]);
    }
}


int is_valid_identifier(const char *arg) {
    // 変数名が無効な場合（例: 数字で始まる、特殊文字を含む）
    if (!arg || (!isalpha(arg[0]) && arg[0] != '_')) {
        return 0;
    }
    for (int i = 1; arg[i] && arg[i] != '='; i++) {
        if (!isalnum(arg[i]) && arg[i] != '_') {
            return 0;
        }
    }
    return 1;
}


int export_variable(char ***env, char *arg) {
    if (!arg) {
        print_env(*env); // 引数なしの場合、環境変数一覧を表示
        return 0;
    }

    // `is_valid_identifier()` を `=` なしの変数名にも適用
    if (!is_valid_identifier(arg)) {
        fprintf(stderr, "export: `%s': not a valid identifier\n", arg);
        return 1; // Bash と同じ exit code 1
    }

    // `=` を含まない場合はエラーにはしない（Bash と同じ仕様）
    if (!strchr(arg, '=')) {
        return 0;
    }

    // 既存の変数を更新
    int i = 0;
    size_t name_len = strchr(arg, '=') - arg;
    for (; (*env)[i]; i++) {
        if (strncmp((*env)[i], arg, name_len) == 0 && (*env)[i][name_len] == '=') {
            free((*env)[i]);
            (*env)[i] = strdup(arg);
            if (!(*env)[i]) {
                perror("strdup failed");
                return 1;
            }
            return 0;
        }
    }

    // 新しい環境変数を追加
    char **new_env = realloc(*env, sizeof(char *) * (i + 2));
    if (!new_env) {
        perror("realloc failed");
        return 1;
    }
    *env = new_env;
    (*env)[i] = strdup(arg);
    if (!(*env)[i]) {
        perror("strdup failed");
        return 1;
    }
    (*env)[i + 1] = NULL; // NULL 終端を追加
    return 0;
}

int unset_variable(char ***env, char *arg) {
    int i = 0, j = 0;

    for (; (*env)[i]; i++) {
        // 環境変数の名前が一致し、'='で区切られている場合に削除
        if (strncmp((*env)[i], arg, strlen(arg)) == 0 && (*env)[i][strlen(arg)] == '=') {
            free((*env)[i]);
        } else {
            (*env)[j++] = (*env)[i];
        }
    }

    (*env)[j] = NULL;

    // Bashと同じ動作に合わせ、変数が見つからなくても終了コードは0とする
    return 0;  // 変数が見つからなくても、終了コードは0にする（Bashに合わせる）
}


// int main(int argc, char **argv, char **envp) {
//     char **environment = copy_environment(envp);
//     char input[256];

//     while (1) {
//         printf("minishell> ");
//         fgets(input, 256, stdin);
//         input[strcspn(input, "\n")] = '\0'; // 改行を除去

//         if (strcmp(input, "cd") == 0) {
//             // 引数がない場合はホームディレクトリに移動
//             change_directory(NULL);
//         } else if (strncmp(input, "cd ", 3) == 0) {
//             // 引数がある場合は指定されたパスに移動
//             change_directory(input + 3);
//         } else if (strcmp(input, "exit") == 0) {
//             exit_shell(environment);
//         } else if (strncmp(input, "echo ", 5) == 0) {
//             echo_command(input + 5);
//         } else if (strcmp(input, "pwd") == 0) {
//             print_working_directory();
//         } else if (strcmp(input, "env") == 0) {
//             print_environment(environment);
//         } else if (strncmp(input, "export ", 7) == 0) {
//             export_variable(&environment, input + 7);
//         } else if (strncmp(input, "unset ", 6) == 0) {
//             unset_variable(&environment, input + 6);
//         } else {
//             printf("Unsupported command: %s\n", input);
//         }
//     }

//     free_environment(environment);
//     return 0;
// }





