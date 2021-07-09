/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:20:37 by rchelsea          #+#    #+#             */
/*   Updated: 2020/11/25 22:01:30 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void*
	ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ddst;
	unsigned char	*ssrc;
	unsigned char	d;
	size_t			i;

	ddst = (unsigned char*)dst;
	ssrc = (unsigned char*)src;
	d = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		ddst[i] = ssrc[i];
		if (ssrc[i] == d)
		{
			return ((void *)ddst + i + 1);
		}
		i++;
	}
	return (0);
}
