/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:12:03 by karai             #+#    #+#             */
/*   Updated: 2025/01/12 12:45:00 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "linked_list.h"
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

bool			is_blank(char c);
int				is_delimeter(char *str);
char			*strdup_len(char *str, size_t n);

char			*delete_blank_start_end(char *input);
size_t			split_len(char *input);
t_linked_list	*parser(char *input);

#endif
