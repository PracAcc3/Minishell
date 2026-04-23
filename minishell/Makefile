NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I includes
LDFLAGS = -lreadline

SRCS    = src/main.c
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all