/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:45:05 by karai             #+#    #+#             */
/*   Updated: 2024/10/30 20:23:50 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 == SIZE_MAX - len_s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, (void *)s1, len_s1);
	ft_memcpy(&ptr[len_s1], (void *)s2, len_s2);
	ptr[len_s1 + len_s2] = '\0';
	return (ptr);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*s;

// 	s = ft_strjoin("", "42");
// 	printf("%s\n", s);
// }
