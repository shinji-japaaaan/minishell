/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:12:03 by karai             #+#    #+#             */
/*   Updated: 2025/01/17 22:29:46 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libft/libft.h"

// TokenTypeの定義（必要な場合）
typedef enum e_token_type
{
    TYPE_COMMAND,
    TYPE_PIPE,
    TYPE_REDIRECT_IN,
    TYPE_REDIRECT_OUT,
    TYPE_HEREDOC,
    TYPE_REDIRECT_APPEND,
    TYPE_DEFAULT
}   TokenType;

// リスト構造体の定義
typedef struct s_linked_list
{
    char            *content;
    TokenType       token_type;
    struct s_linked_list *next;
}   t_linked_list;

// 関数プロトタイプ

// expansion.c
bool    is_name_character(char c);
char    *get_env_str(char *str, size_t *len);
char    *replace_to_env_val(char *str, char *env_str);
char    *expansion(char *str);

// linked_list.c
void    linked_list_print(t_linked_list *list_head);
void    linked_list_print_with_token(t_linked_list *list_head);
void    linked_list_free(t_linked_list *list_head);
void    linked_list_append(t_linked_list *list_head, char *str);
t_linked_list    *linked_list_init(t_linked_list *new_node);

// parser.c
t_linked_list    remove_quotes_from_tokens(t_linked_list *list_head);
void    expand_env_variables_in_list(t_linked_list *list_head);
t_linked_list    *parser(char *input);

// remove_quote.c
size_t  remove_quote_get_newlen(char *str);
char    *remove_quote(char *str);

// tokenize.c
TokenType   get_token_type(char *str);
void        assign_token_types(t_linked_list *list_head);
int         is_delimeter(char *str);
size_t      split_len(char *input);
void        tokenize_input(t_linked_list *head, char *input);

// utils.c
char    *strdup_len(char *str, size_t n);
bool    is_blank(char c);
void    ft_strcpy(char *dst, char *src);

#endif
/* ************************************************************************** */

