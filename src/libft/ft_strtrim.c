/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:10:41 by karai             #+#    #+#             */
/*   Updated: 2024/11/04 19:10:32 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_trim_set(const char *set, unsigned char trim[256])
{
	while (*set != '\0')
	{
		trim[(unsigned char)(*set)] = 1;
		set += 1;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned char	trim[256];
	size_t			s1_len;
	char			*str;
	size_t			start;
	size_t			end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	ft_memset(trim, 0, 256);
	ft_trim_set(set, trim);
	s1_len = ft_strlen(s1);
	start = 0;
	end = s1_len;
	while (trim[(unsigned char)(s1[start])])
		start += 1;
	end -= 1;
	while (end > start && trim[(unsigned char)(s1[end])])
		end -= 1;
	str = (char *)malloc(end - start + 2);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s1[start], (end - start + 2));
	return (str);
}

// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
// 	char *s = ft_strtrim("   xxxtripouille   xxx", " x");
// 	printf("%s\n",s);
// 	printf("%ld\n",strlen(s));
// 	// char	*s1 = "   \t \n\nHello \t  Please\n Trim me !\n   \n \\n  ";
// 	// char	*s2 = "Hello \t  Please\n Trim me !";
// 	// printf("%s\n",ft_strtrim(s1, " \n\t"));
// 	// // char *s3 = "  \t \t \n \n\n\n\t";
// 	// // char *s4 = "";
// 	// // char *ret = ft_strtrim(s3, " \n\t");
// 	// // printf("%s\n",ret);
// 	char *a = ft_strtrim("", "");
// 	printf("%s\n",a);
// }
