NAME	=	philo

CC		=	gcc

CFLAGS 	=	-Wall -Wextra -Werror -pthread

SRC		:=	main.c threads.c utils.c ft_isdigit.c ft_atoi.c

OBJ 	:=	${SRC:.c=.o}

HEADERS	=	philo.h

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
