/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 07:50:00 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/12 07:50:27 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <string.h>

int match_pattern(const char *pattern, const char *str) {
    while (*pattern && *str) {
        if (*pattern == '*') {
            pattern++;
            if (!*pattern) return 1;
            while (*str) {
                if (match_pattern(pattern, str)) return 1;
                str++;
            }
            return 0;
        } else if (*pattern == *str) {
            pattern++;
            str++;
        } else {
            return 0;
        }
    }
    return !*pattern && !*str;
}

void expand_wildcard(const char *pattern) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("."); // 現在のディレクトリをオープン
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // match_pattern を使ってパターンとファイル名を比較
        if (match_pattern(pattern, entry->d_name)) {
            // パターンにマッチするファイル名を出力
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main() {
    expand_wildcard("*.txt");  // 例: *.txt をパターンとして渡す
    return 0;
}
