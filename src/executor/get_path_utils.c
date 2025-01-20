/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 02:47:23 by karai             #+#    #+#             */
/*   Updated: 2025/01/19 05:50:53 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_access(char *full_path)
{
	if (access(full_path, F_OK) == 0)
	{
		if (access(full_path, X_OK) == 0)
			return (2);
		else
			return (1);
	}
	return (0);
}

bool	is_full_relative_path(char *str)
{
	if (str == NULL)
		return (false);
	if (str[0] == '.' || str[0] == '/')
		return (true);
	return (false);
}
