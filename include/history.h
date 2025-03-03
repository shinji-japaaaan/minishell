/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:10:32 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/22 07:15:35 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define HISTORY_FILE ".minishell_history"
# define BUFFER_SIZE 1024
# define MAX_HISTORY 100

typedef struct s_History
{
	char	**entries;
	int		count;
	int		max_size;
	char	*history_path;
}			t_History;

t_History	*init_history(int max_size);
void		add_to_history(t_History *history, const char *line);
void		save_history_to_file(const char *filename, t_History *history);
void		load_history_from_file(const char *filename, t_History *history);
void		free_history(t_History *history);

#endif
