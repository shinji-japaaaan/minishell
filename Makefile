NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRCS = src/main.c \
       src/parser/tokenizer.c \
       src/parser/parser.c \
       src/executor/executor.c \
       src/executor/builtins.c \
       src/executor/redirection.c \
       src/signals/signals.c \
       src/utils/utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
