/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:17:16 by karai             #+#    #+#             */
/*   Updated: 2024/11/09 18:03:50 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	ans;
	int		pm;

	ans = 0;
	pm = 1;
	while (*nptr == '\f' || *nptr == '\n' || *nptr == '\r' || *nptr == '\t'
		|| *nptr == '\v' || *nptr == ' ')
		nptr += 1;
	if (*nptr == '-')
		pm = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr += 1;
	while (*nptr <= '9' && *nptr >= '0')
	{
		if (pm == 1 && (ans > LONG_MAX / 10 || ((LONG_MAX - ans * 10) < (*nptr
						- '0'))))
			return ((int)LONG_MAX);
		if (ans != 0 && pm == -1 && ((ans > -1 * (LONG_MIN / 10)) || (-1
					* (LONG_MIN + ans * 10)) < (*nptr - '0')))
			return ((int)LONG_MIN);
		ans = ans * 10 + (*nptr - '0');
		nptr += 1;
	}
	return (ans * pm);
}

// #include <limits.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*a;
// 	char	*n;

// 	printf("%ld\n", LONG_MIN);
// 	printf("%ld\n", LONG_MAX);
// 	a = "-9223372036854775809";
// 	printf("%d\n", ft_atoi(a));
// 	printf("%d\n", atoi(a));
// 	a = "9223372036854775811";
// 	printf("%d\n", ft_atoi(a));
// 	printf("%d\n", atoi(a));
// 	n = "\t\v\f\r\n \f-06050";
// 	printf("%d\n", ft_atoi(n));
// 	printf("%d\n", atoi(n));
// }
