NAME = philo
SRCS = src/main.c src/arg_check.c src/philo.c\
	   src/time.c src/create_philos.c src/simulation.c\
	   src/mutexes.c src/utils.c
OBJS = $(SRCS:%.c=%.o)
HEADER = philo.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all