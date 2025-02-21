/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:12:05 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/22 07:18:46 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_history(t_History *history)
{
	int	i;

	if (!history)
		return ;
	free(history->history_path);
	if (history->entries)
	{
		i = 0;
		while (i < history->count)
		{
			free(history->entries[i]);
			i++;
		}
		free(history->entries);
	}
	free(history);
}
