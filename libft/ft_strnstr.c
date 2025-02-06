/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:52:05 by karai             #+#    #+#             */
/*   Updated: 2024/10/30 21:03:42 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	judge(const char *str_part, const char *to_find, size_t len,
		size_t idx)
{
	size_t	i;

	i = 0;
	while (str_part[i] != '\0' && to_find[i] != '\0' && (i + idx) < len)
	{
		if (str_part[i] != to_find[i])
			return (0);
		i += 1;
	}
	if (to_find[i] == '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (little[0] == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] != '\0')
	{
		if (judge(&big[i], little, len, i))
			return ((char *)&big[i]);
		if (i == SIZE_MAX)
			return (NULL);
		i += 1;
	}
	return (NULL);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	haystack[30] = "aaabcabcd";
// 	char	*str;

// 	// char needle[10] = "aabc";
// 	str = ft_strnstr(haystack, "cd", 8);
// 	printf("%p\n", str);
// }
