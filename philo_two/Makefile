NAME = philo_two
SRCS =	srcs/main.c \
		srcs/philo_two.c \
		srcs/tools.c \
		srcs/ft_itoa.c

OBJS = $(SRCS:.c=.o)
CC = gcc
INCLUDES = ./includes/
HEADERS = philo_two.h
CFLAGS = -Werror -Wall -Wextra -g3 -pthread -I $(INCLUDES)

SRCS_FILE = SRCS


all: $(NAME)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re