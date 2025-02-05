/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:12:03 by karai             #+#    #+#             */
/*   Updated: 2025/02/06 21:17:18 by sishizaw         ###   ########.fr       */
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
	int						pipefd[2];
	int						fd;
	int						fd1;
	int						stdio_backup;
	struct s_redirect		*next;
}							t_redirect;

typedef struct s_cmd_invoke
{
	char					**cmd_list;
	t_redirect				*redirect_head;
	struct s_cmd_invoke		*next;
	pid_t					pid;
	int						*bef_pipefd;
	int						nxt_pipefd[2];
	int						in_fd;
	int						out_fd;
}							t_cmd_invoke;

typedef struct s_cmd_state
{
	t_linked_list	*list_ptr_temp;
	t_cmd_invoke	*cmd_ptr_temp;
	bool			is_filename;
	TokenType		bef_token_type;
	bool			is_pipe;
	size_t			cmd_len;
	size_t			i;
}	t_cmd_state;

// 関数プロトタイプ

// expansion.c
bool						is_name_character(char c);
char						*get_env_str(char *str, size_t *strdup_len);
char						*replace_to_env_val(char *str, char *env_str,
								int last_status);
char						*expansion(char *str, int last_status);

// linked_list.c
void						linked_list_print(t_linked_list *list_head);
void						linked_list_print_with_token(t_linked_list *list_head);
void						linked_list_free(t_cmd_invoke *list_head);
void						linked_list_append(t_linked_list *list_head,
								char *str);
t_linked_list				*linked_list_init(t_linked_list *head);

// parser.c
t_linked_list				remove_quotes_from_tokens(t_linked_list *list_head);
void						expand_env_variables_in_list(t_linked_list *list_head,
								int last_status);
t_cmd_invoke				*parser(char *input, int last_status);

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
t_redirect					*redirect_init(t_redirect *new_node);
t_cmd_invoke				*cmd_invoke_init(t_cmd_invoke *new_node);
size_t						ft_cmd_len(t_linked_list *node);
t_redirect					*redirect_append(t_redirect *redirect_head,
								char *content, TokenType token_type);
t_cmd_invoke				*make_cmd(t_linked_list *list_head,
								t_cmd_invoke *cmd_head);

// parse_error.c
bool						parse_error_quote(char *input);
bool						parse_error_unexpected_str_judge(char *str);
bool						parse_error_unexpected_str(char *input);
bool						parse_error_last_token(t_linked_list *head);
bool						parse_error_consecutive_redirect(t_linked_list *head);
bool						parse_error_consecutive_pipe(t_linked_list *head);

// heredoc.c
void						heredoc_read(t_redirect *node, char *str_eof);
int						heredoc_redirect_list(t_redirect *head_redirect_in);
void						heredoc_main(t_cmd_invoke *head_cmd);
void						heredoc_close(t_cmd_invoke *node);
void						heredoc_read_main(t_redirect *head_redirect);
void						heredoc_read_rev(t_redirect *node, char *str_eof);
void						heredoc_pipe_open(t_redirect *head_redirect);

#endif

/* ************************************************************************** */
