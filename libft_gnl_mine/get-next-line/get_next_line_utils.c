/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:50:52 by rchelsea          #+#    #+#             */
/*   Updated: 2021/01/04 14:54:41 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strmove(char *ddst, char *ssrc, size_t len)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = len;
	if (ddst == NULL && ssrc == NULL)
		return (NULL);
	if (ssrc > ddst)
	{
		while (ssrc[i] != '\0')
		{
			ddst[i] = ssrc[i];
			i++;
		}
		ddst[i] = '\0';
	}
	else
	{
		while (len--)
			ddst[len] = ssrc[len];
		ddst[j] = '\0';
	}
	return (ddst);
}
