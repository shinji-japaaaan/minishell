/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:10:32 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/13 10:23:23 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
#define HISTORY_H

// 履歴関連の定数定義
#define HISTORY_FILE ".minishell_history"
#define BUFFER_SIZE 1024
#define MAX_HISTORY 100

// 履歴管理用構造体
typedef struct {
    char **entries;
    int count;
    int max_size;
} History;

// 履歴管理関数のプロトタイプ宣言
History *init_history(int max_size);
void add_to_history(History *history, const char *line);
void save_history_to_file(const char *filename, History *history);
void load_history_from_file(const char *filename, History *history);
void free_history(History *history);

#endif /* HISTORY_H */


