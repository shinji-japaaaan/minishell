/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:12:03 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 16:30:46 by karai            ###   ########.fr       */
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
}							t_TokenType;

// リスト構造体の定義
typedef struct s_linked_list
{
	char					*content;
	t_TokenType				token_type;
	struct s_linked_list	*next;
}							t_linked_list;

typedef struct s_redirect
{
	char					*filename;
	t_TokenType				token_type;
	int						pipefd[2];
	int						fd;
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
	t_linked_list			*list_ptr_temp;
	t_cmd_invoke			*cmd_ptr_temp;
	bool					is_filename;
	t_TokenType				bef_token_type;
	bool					is_pipe;
	size_t					cmd_len;
	size_t					i;
}							t_cmd_state;

// 関数プロトタイプ

// expansion.c
bool						is_nc(char c);
char						*get_env_str(char *str);
char						*replace_to_env_val(char *str, char *env_str,
								int last_status);
char						*expansion(char *str, int last_status, char **env);
char						*handle_dollar(char *str, size_t *i,
								int last_status, char **env);
char						*replace_env_var(char *str, char *env_str,
								int last_status, char **env);
char						*get_env_value(char *env_str, int last_status,
								char **env);

// linked_list.c
void						linked_list_free(t_cmd_invoke *list_head);
t_linked_list				*linked_list_append(t_linked_list *list_head,
								char *str);
t_linked_list				*linked_list_init(t_linked_list *head);

// parser.c
t_linked_list				remove_quotes_from_tokens(t_linked_list *list_head);
t_linked_list				*expand_env_var_in_list(t_linked_list *list_head,
								int last_status, char **env);
void						change_emp_to_null(t_linked_list *head);
t_cmd_invoke				*parser(char *input, int last_status, char **env);

// remove_quote.cS
size_t						remove_quote_get_newlen(char *str);
char						*remove_quote(char *str);

// tokenize.c
t_TokenType					get_token_type(char *str);
void						assign_token_types(t_linked_list *list_head);
int							is_delimeter(char *str);
size_t						split_len(char *input);
t_linked_list				*tokenize_input(t_linked_list *head, char *input);

// utils.c
char						*strdup_len(char *str, size_t n);
bool						is_blank(char c);
void						ft_strcpy(char *dst, char *src);
bool						is_nc(char c);

// make_cmd.c
t_redirect					*redirect_init(t_redirect *new_node);
t_cmd_invoke				*cmd_invoke_init(t_cmd_invoke *new_node);
size_t						ft_cmd_len(t_linked_list *node);
t_redirect					*redirect_append(t_redirect *redirect_head,
								char *content, t_TokenType token_type);
t_cmd_invoke				*make_cmd(t_linked_list *list_head,
								t_cmd_invoke *cmd_head);
t_cmd_invoke				*init_new_cmd(t_cmd_invoke *cmd_ptr_temp);
void						init_cmd_list(t_cmd_state *state);

// parse_error.c
bool						parse_error_quote(char *input);
bool						parse_error_unexpected_str_judge(char *str);
bool						parse_error_unexpected_str(char *input);
bool						parse_error_last_token(t_linked_list *head);
bool						parse_error_consec_red(t_linked_list *head);
bool						parse_error_consecutive_pipe(t_linked_list *head);

// heredoc.c
void						heredoc_read(t_redirect *node, char *str_eof,
								char **env, int *last_status);
void						heredoc_redirect_list(t_redirect *head_redirect_in,
								char **env, int *last_status);
void						heredoc_main(t_cmd_invoke *head_cmd, char **env,
								int *last_status);
void						heredoc_close(t_cmd_invoke *node);
void						heredoc_close_nu(t_cmd_invoke *head_cmd,
								t_cmd_invoke *now);
void						heredoc_read_main(t_redirect *head_redirect,
								int *last_status);
void						heredoc_read_rev(t_redirect *node, char *str_eof);
void						heredoc_pipe_open(t_redirect *head_redirect);
char						*heredoc_expansion(char *input, char **env,
								int *last_status);
void						heredoc_read_loop(char *str_eof, char **env,
								int pipefd[2], int *last_status);

// ft_getenv.c
int							ft_cmp_for_getenv(char *str, char *env_str,
								size_t *len);
char						*ft_getenv(char *str, char **env);

// sinal.c
void						setup_signal_handler_heredoc(void);
void						handle_sigint_heredoc(int signum);
int							check_interrupt(void);

#endif

/* ************************************************************************** */
