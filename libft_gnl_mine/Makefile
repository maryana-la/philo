# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 15:41:42 by rchelsea          #+#    #+#              #
#    Updated: 2021/05/29 18:55:26 by rchelsea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
SRCS	=	ft_memcpy.c ft_memmove.c ft_memset.c ft_atoi.c ft_strchr.c ft_bzero.c ft_strlcat.c \
			ft_isalnum.c ft_strlcpy.c ft_isalpha.c ft_strlen.c ft_isascii.c	ft_strncmp.c ft_isdigit.c \
			ft_strnstr.c ft_isprint.c ft_strrchr.c ft_memccpy.c ft_tolower.c ft_memchr.c ft_toupper.c \
			ft_memcmp.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c \
			ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			get-next-line/get_next_line.c get-next-line/get_next_line_utils.c
OBJS	=	${SRCS:.c=.o}
FLAGS	=	-Wall -Wextra -Werror
CC		=	gcc
RM		=	rm -f

%.o:	%.c	libft.h
			@${CC} ${FLAGS} -c $< -o $@

${NAME}:	${OBJS}
			 ar rc ${NAME} ${OBJS}
			 ranlib ${NAME}

all:		${NAME}

clean:
			@${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
