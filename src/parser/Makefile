# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I../libft

# Source files and object files
SRC = expansion.c linked_list.c parser.c remove_quote.c tokenize.c utils.c main.c
OBJ = $(SRC:.c=.o)

# Target executable
NAME = minishell

# Libft settings
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Phony targets
.PHONY: all clean fclean re
