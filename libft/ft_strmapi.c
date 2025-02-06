/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:54:17 by karai             #+#    #+#             */
/*   Updated: 2024/10/30 19:58:08 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	length;
	char			*new_str;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	if (length == UINT_MAX)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (length + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		new_str[i] = f(i, s[i]);
		i += 1;
	}
	new_str[i] = '\0';
	return (new_str);
}

// #include <stdio.h>
// char addOne(unsigned int i, char c) {return (i + c);}
// int main(void)
// {
// 	char * s = ft_strmapi("1234", addOne);
// 	printf("%s\n",s);
// }
