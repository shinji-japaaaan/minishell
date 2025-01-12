/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:10:32 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/11 08:18:39 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
#define HISTORY_H

#include "minishell.h"  // minishell.h をインクルードして、共通の定義を再利用

#define HISTORY_FILE ".minishell_history"
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

