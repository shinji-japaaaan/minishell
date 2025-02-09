/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:15:51 by karai             #+#    #+#             */
/*   Updated: 2025/02/09 13:10:35 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	perror_exit(char *str, char **str_array1, char **str_array2,
		int exit_status)
{
	perror(str);
	free2dim(&str_array1);
	free2dim(&str_array2);
	exit(exit_status);
}
