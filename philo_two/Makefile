NAME = philo_two

CC = gcc
HEADERS = philo_two.h
CFLAGS = -Werror -Wall -Wextra -g3
SRCS =	main.c \
		philo_two.c \
		tools.c

SRCS_FILE = SRCS

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re