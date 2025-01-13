/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:12:03 by karai             #+#    #+#             */
/*   Updated: 2025/01/13 21:07:42 by karai            ###   ########.fr       */
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

// expansion.c
bool			is_name_character(char c);
char			*get_env_str(char *str, size_t *len);
void			ft_strcpy(char *dst, char *src);
char			*replace_to_env_val(char *str, char *env_str);
char			*expansion(char *str);

// tokenize.c
TokenType		get_token_type(char *str);
void			linked_list_tokenize(t_linked_list *list_head);

// remove_quote.c
size_t			remove_quote_get_newlen(char *str);
char			*remove_quote(char *str);
t_linked_list	linked_list_remove_quote(t_linked_list *list_head);

#endif
