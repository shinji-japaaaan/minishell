/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:09:54 by karai             #+#    #+#             */
/*   Updated: 2024/11/04 16:36:58 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_minus(long long *nb, int fd)
{
	if (*nb < 0)
	{
		*nb = -*nb;
		write(fd, "-", 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int			div;
	long long	tmp;
	char		num_char;
	long long	nb_long;

	nb_long = (long long)n;
	ft_putnbr_minus(&nb_long, fd);
	div = 1;
	tmp = nb_long;
	while (tmp / 10 != 0)
	{
		div *= 10;
		tmp = tmp / 10;
	}
	while (div != 0)
	{
		num_char = '0' + (nb_long / div % 10);
		write(fd, &num_char, 1);
		div = div / 10;
	}
}
