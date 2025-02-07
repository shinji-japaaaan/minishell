/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal..c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 07:01:59 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/08 07:02:27 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_interrupt(void)
{
	if (global_pid)
		rl_done = 1;
	return (0);
}

void	handle_sigint_heredoc(int signum)
{
	(void)signum;
	global_pid = 1;
}

void	setup_signal_handler_heredoc(void)
{
	global_pid = 0;
	rl_done = 0;
	signal(SIGINT, handle_sigint_heredoc);
}