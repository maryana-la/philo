# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 15:49:58 by rchelsea          #+#    #+#              #
#    Updated: 2021/07/27 15:49:59 by rchelsea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	gcc

CFLAGS 	=	-Wall -Wextra -Werror -pthread -g

SRC		:=	main.c threads.c utils.c ft_isdigit.c ft_atoi.c

HEADERS	=	philo.h

O_FOLD	=	objs/
OBJ	:=	$(addprefix $(O_FOLD), $(SRC:.c=.o))

$(O_FOLD)%.o: %.c $(HEADER)
	@mkdir -p objs
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
	@rm -rf $(O_FOLD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
