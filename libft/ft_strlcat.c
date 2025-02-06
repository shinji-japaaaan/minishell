/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:56:08 by karai             #+#    #+#             */
/*   Updated: 2024/10/30 20:35:40 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (size + src_len);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] != 0 && i < size - dst_len - 1)
	{
		dst[dst_len + i] = src[i];
		i += 1;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}

// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
// 	ft_strlcat(NULL, "abcd", 0);
// 	strncat("abcd", NULL, 0);
// }
