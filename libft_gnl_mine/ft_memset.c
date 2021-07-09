/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:01:26 by rchelsea          #+#    #+#             */
/*   Updated: 2020/11/19 23:50:23 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*mb;
	size_t			l;

	l = 0;
	mb = (unsigned char*)b;
	while (l < len)
	{
		mb[l] = c;
		l++;
	}
	return ((unsigned char *)b);
}
