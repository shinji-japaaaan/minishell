/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:12:03 by karai             #+#    #+#             */
/*   Updated: 2025/01/21 08:15:17 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

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
}							TokenType;

// リスト構造体の定義
typedef struct s_linked_list
{
	char					*content;
	TokenType				token_type;
	struct s_linked_list	*next;
}							t_linked_list;

typedef struct s_redirect
{
	char					*filename;
	TokenType				token_type;
	int						fd;
	int						stdio_backup;
	struct s_redirect		*next;
}							t_redirect;

typedef struct s_cmd_invoke
{
	char					**cmd_list;
	t_redirect				*redirect_in_head;
	t_redirect				*redirect_out_head;
	struct s_cmd_invoke		*next;
	pid_t					pid;
	int						*bef_pipefd;
	int						nxt_pipefd[2];
	int						in_fd;
	int						out_fd;
}							t_cmd_invoke;

// 関数プロトタイプ

// expansion.c
bool						is_name_character(char c);
char						*get_env_str(char *str, size_t *len);
char						*replace_to_env_val(char *str, char *env_str);
char						*expansion(char *str);

// linked_list.c
void						linked_list_print(t_linked_list *list_head);
void						linked_list_print_with_token(t_linked_list *list_head);
void						linked_list_free(t_cmd_invoke *list_head);
void						linked_list_append(t_linked_list *list_head,
								char *str);
t_linked_list				*linked_list_init(t_linked_list *head);

// parser.c
t_linked_list				remove_quotes_from_tokens(t_linked_list *list_head);
void						expand_env_variables_in_list(t_linked_list *list_head);
t_cmd_invoke				*parser(char *input);

// remove_quote.cS
size_t						remove_quote_get_newlen(char *str);
char						*remove_quote(char *str);

// tokenize.c
TokenType					get_token_type(char *str);
void						assign_token_types(t_linked_list *list_head);
int							is_delimeter(char *str);
size_t						split_len(char *input);
void						tokenize_input(t_linked_list *head, char *input);

// utils.c
char						*strdup_len(char *str, size_t n);
bool						is_blank(char c);
void						ft_strcpy(char *dst, char *src);

// make_cmd.c
size_t						ft_cmd_len_list(t_cmd_invoke *head);
t_redirect					*redirect_init(t_redirect *new_node);
t_cmd_invoke				*cmd_invoke_init(t_cmd_invoke *new_node);
size_t						ft_cmd_len(t_linked_list *node);
t_redirect					*redirect_append(t_redirect *redirect_head,
								char *content, TokenType token_type);
t_cmd_invoke				*make_cmd(t_linked_list *list_head,
								t_cmd_invoke *cmd_head);

#endif

/* ************************************************************************** */
