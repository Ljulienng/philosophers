NAME = philo_one
SRCS =	srcs/main.c \
		srcs/philo_one.c \
		srcs/tools.c \
		srcs/ft_itoa.c

OBJS = $(SRCS:.c=.o)
CC = clang
INCLUDES = ./includes/
HEADERS = philo_one.h
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