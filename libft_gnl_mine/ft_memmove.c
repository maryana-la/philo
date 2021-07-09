/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:03:58 by rchelsea          #+#    #+#             */
/*   Updated: 2020/11/20 22:00:05 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ddst;
	unsigned char	*ssrc;
	size_t			i;

	ddst = (unsigned char *)dst;
	ssrc = (unsigned char *)src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (ssrc > ddst)
	{
		while (i < len)
		{
			ddst[i] = ssrc[i];
			i++;
		}
	}
	else
	{
		while (len--)
			ddst[len] = ssrc[len];
	}
	return (dst);
}
