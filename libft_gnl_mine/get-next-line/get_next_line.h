/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:50:52 by rchelsea          #+#    #+#             */
/*   Updated: 2021/01/03 23:21:44 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 48
# endif

int		get_next_line(int fd, char **line);
int		error_free (char **s1, char **s2);
int		return_value(int bytes_read, char **search_n, char **buffer);
char	*ft_strzero(size_t size);
char	*ft_strmove(char *ddst, char *ssrc, size_t len);
char	*check_rest(char **rest, char **line);

#endif
