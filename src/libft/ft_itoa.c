/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:59:36 by karai             #+#    #+#             */
/*   Updated: 2024/10/28 20:25:24 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_digit_len(long n)
{
	size_t	digit_len;

	digit_len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		digit_len += 1;
		n *= -1;
	}
	while (n != 0)
	{
		digit_len += 1;
		n /= 10;
	}
	return (digit_len);
}

char	*ft_itoa(int n)
{
	size_t		digit_len;
	char		*str;
	long long	n_long;

	n_long = (long long)n;
	digit_len = ft_digit_len(n_long);
	str = (char *)malloc(sizeof(char) * (digit_len + 1));
	if (str == NULL)
		return (NULL);
	str[digit_len] = '\0';
	if (n_long == 0)
		str[0] = '0';
	if (n_long < 0)
	{
		str[0] = '-';
		n_long *= -1;
	}
	digit_len -= 1;
	while (n_long != 0)
	{
		str[digit_len] = '0' + (n_long % 10);
		digit_len -= 1;
		n_long /= 10;
	}
	return (str);
}

// #include <limits.h>
// #include <stdio.h>
// int main(void)
// {
// 	printf("%d\n", INT_MIN);
// 	char *s = ft_itoa(INT_MIN);
// 	printf("%s\n",s);
// }
