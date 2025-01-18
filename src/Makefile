# Target executable
NAME = minishell

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I./libft

# Source files
SRCS = main.c \
       parser/tokenize.c \
       parser/parser.c \
       parser/expansion.c \
       parser/linked_list.c \
       parser/remove_quote.c \
       parser/utils.c \
	   ../bonus/history.c

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
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Phony targets
.PHONY: all clean fclean re

