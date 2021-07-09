/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 20:14:19 by rchelsea          #+#    #+#             */
/*   Updated: 2020/11/22 21:54:51 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	string;

	i = 0;
	if (s && fd > 0)
	{
		while (s[i])
		{
			string = s[i];
			write(fd, &string, 1);
			i++;
		}
		write(fd, "\n", 1);
	}
}
