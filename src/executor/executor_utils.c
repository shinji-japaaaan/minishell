/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:15:51 by karai             #+#    #+#             */
/*   Updated: 2025/01/19 05:50:40 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	perror_exit(char *str, char **str_array1, char **str_array2,
		int exit_status)
{
	perror(str);
	free2dim(str_array1);
	free2dim(str_array2);
	exit(exit_status);
}

