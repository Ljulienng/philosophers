NAME = philo_three

CC = gcc
HEADERS = philo_three.h
CFLAGS = -Werror -Wall -Wextra -g
SRCS =	main.c \
		philo_three.c \
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