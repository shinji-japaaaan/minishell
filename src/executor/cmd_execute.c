/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:11:24 by karai             #+#    #+#             */
/*   Updated: 2025/02/09 13:10:31 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_execute_first(t_cmd_invoke *node)
{
	dup2(node->nxt_pipefd[1], 1);
	close(node->nxt_pipefd[0]);
	close(node->nxt_pipefd[1]);
}

void	cmd_execute_last(t_cmd_invoke *node)
{
	dup2(node->bef_pipefd[0], 0);
	close(node->bef_pipefd[0]);
	close(node->bef_pipefd[1]);
}

void	cmd_execute_middle(t_cmd_invoke *node)
{
	dup2(node->bef_pipefd[0], 0);
	dup2(node->nxt_pipefd[1], 1);
	close(node->bef_pipefd[0]);
	close(node->bef_pipefd[1]);
	close(node->nxt_pipefd[0]);
	close(node->nxt_pipefd[1]);
}
