/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:12:05 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/22 06:22:38 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_history(t_History *history)
{
	int	i;

	if (!history)
		return ;
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
