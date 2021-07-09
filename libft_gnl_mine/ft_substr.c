/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 22:50:51 by rchelsea          #+#    #+#             */
/*   Updated: 2020/11/22 21:43:01 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	i;

	if (!s)
		return (NULL);
	new = (char *)malloc(len + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	if (ft_strlen(s) <= start)
	{
		*new = 0;
		return (new);
	}
	if (ft_strlen(s) > start)
	{
		while (s[start] && i < len)
			new[i++] = s[start++];
		new[i] = '\0';
		return (new);
	}
	else
		return (0);
}
