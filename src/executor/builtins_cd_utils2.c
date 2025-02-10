/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:59:02 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/10 21:14:51 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int print_error(const char *msg)
{
    write(STDERR_FILENO, msg, ft_strlen(msg));
    return (1);
}

char *resolve_path(char *path)
{
    if (!path || ft_strcmp(path, "~") == 0)
        return getenv("HOME");
    if (ft_strcmp(path, "$PWD") == 0)
        return getenv("PWD");
    return path;
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*d;
	size_t	i;
	size_t	j;

	d = dest;
	i = ft_strlen(dest);
	j = 0;
	while (src[j])
	{
		d[i] = src[j];
		i++;
		j++;
	}
	d[i] = '\0';
	return (dest);
}
