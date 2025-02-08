# Target executable
NAME = minishell

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I./libft -g -O0

# Source files
SRCS = src/main.c \
	   src/process_shell/process_shell.c \
	   src/process_shell/signal_main.c \
	   src/process_shell/signal_exec.c \
	   src/process_shell/history.c \
       src/parser/tokenize.c \
       src/parser/parser.c \
       src/parser/expansion.c \
       src/parser/linked_list.c \
       src/parser/remove_quote.c \
       src/parser/utils.c \
	   src/parser/make_cmd.c \
	   src/parser/cmd_init.c \
	   src/parser/parse_error1.c \
	   src/parser/parse_error2.c \
	   src/parser/heredoc.c \
	   src/parser/ft_getenv.c\
	   src/parser/signal.c\
	   src/executor/builtins.c \
	   src/executor/builtins_utils.c \
	   src/executor/builtins_export_utils.c \
	   src/executor/executor.c \
	   src/executor/cmd_execute.c \
	   src/executor/executor_utils.c \
	   src/executor/get_path.c \
	   src/executor/get_path_utils.c \
	   src/executor/free1.c \
	   src/executor/free2.c \
	   src/executor/redirection.c \
	   src/executor/handle_redirect.c\


# Object files (SRCSから.oファイルを生成)
OBJS = $(SRCS:.c=.o)

# Libft settings
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Phony targets
.PHONY: all clean fclean re

