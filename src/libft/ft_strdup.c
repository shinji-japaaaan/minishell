/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:25:02 by karai             #+#    #+#             */
/*   Updated: 2024/10/30 19:50:34 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	src_len;
	char	*copy_src;
	size_t	i;

	src_len = ft_strlen(s);
	if (src_len == SIZE_MAX)
		return (NULL);
	copy_src = (char *)malloc(sizeof(char) * (src_len + 1));
	if (copy_src == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		copy_src[i] = s[i];
		i += 1;
	}
	copy_src[src_len] = '\0';
	return (copy_src);
}
