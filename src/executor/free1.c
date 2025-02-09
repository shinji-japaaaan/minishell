/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:22:29 by karai             #+#    #+#             */
/*   Updated: 2025/02/09 13:11:54 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free1dim(char **str)
{
	if (*str == NULL)
		return ;
	free(*str);
	*str = NULL;
}

void	free2dim(char ***str_array)
{
	size_t	i;

	if (*str_array == NULL)
		return ;
	i = 0;
	while ((*str_array)[i])
	{
		free((*str_array)[i]);
		i += 1;
	}
	free(*str_array);
	*str_array = NULL;
}
