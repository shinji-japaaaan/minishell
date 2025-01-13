/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:17:16 by karai             #+#    #+#             */
/*   Updated: 2024/10/28 20:52:01 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		str++;
		i += 1;
	}
	return (i);
}

// #include <stdio.h>
// #include <limits.h>
// #include <string.h>
// #include <stdint.h>
// int main(void)
// {
// 	printf("%zu\n", SIZE_MAX);
// 	char *str = "aaaaaaaaada";
// 	printf("%ld\n",strlen(str));
// 	printf("%d\n",ft_strlen(str));
// }
