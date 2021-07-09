/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 22:16:23 by rchelsea          #+#    #+#             */
/*   Updated: 2021/01/04 15:10:23 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char	*check_rest(char **rest, char **line)
{
	char *search_n;

	search_n = NULL;
	if (*rest)
	{
		if ((search_n = ft_strchr(*rest, '\n')))
		{
			*search_n = '\0';
			search_n++;
			*line = ft_strdup(*rest);
			ft_strmove(*rest, search_n, ft_strlen(search_n));
		}
		else
		{
			*line = ft_strdup(*rest);
			free(*rest);
			*rest = NULL;
		}
	}
	else
		*line = ft_strzero(1);
	return (search_n);
}

char	*ft_strzero(size_t size)
{
	char *str;

	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (size > 0)
		str[size--] = '\0';
	str[0] = '\0';
	return (str);
}

int		error_free(char **s1, char **s2)
{
	if (*s1)
		free(*s1);
	if (*s2)
		free(*s2);
	return (-1);
}

int		return_value(int bytes_read, char **search_n, char **buffer)
{
	free(*buffer);
	if (bytes_read || *search_n)
		return (1);
	else
		return (0);
}

int		get_next_line(int fd, char **line)
{
	int			bytes_read;
	char		*buffer;
	char		*search_n;
	static char	*rest;
	char		*tmp;
	int count;

	buffer = "\0";
	if (fd < 0 || BUFFER_SIZE < 1 || !line || (count = read(fd, buffer, 0)) < 0 ||
			!(buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	search_n = check_rest(&rest, line);
	while (!search_n && (bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytes_read] = '\0';
		if ((search_n = ft_strchr(buffer, '\n')))
		{
			*search_n = '\0';
			if (!(rest = ft_strdup(++search_n)))
				return (error_free(&rest, &buffer));
		}
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buffer)))
			return (error_free(&rest, &buffer));
		free(tmp);
	}
	return (return_value(bytes_read, &search_n, &buffer));
}
