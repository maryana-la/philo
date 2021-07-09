/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:51:26 by rchelsea          #+#    #+#             */
/*   Updated: 2020/11/24 20:42:23 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	ssize;
	int		i;

	i = 0;
	n = 0;
	if (dst == NULL && src == NULL)
		return (0);
	while (src[i] != '\0')
		i++;
	ssize = i;
	i = 0;
	if (dstsize > 0)
	{
		while ((n < dstsize - 1) && src[i] != '\0')
		{
			dst[i] = src[i];
			n++;
			i++;
		}
		dst[i] = '\0';
	}
	return (ssize);
}
