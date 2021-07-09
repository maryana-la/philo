/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:56:09 by rchelsea          #+#    #+#             */
/*   Updated: 2020/11/24 16:16:14 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(long int num)
{
	size_t numbers;

	numbers = 0;
	if (num <= 0)
	{
		num = -num;
		numbers++;
	}
	while (num != 0)
	{
		num = num / 10;
		numbers++;
	}
	return (numbers);
}

char			*ft_itoa(int n)
{
	char		*str;
	long int	num;
	size_t		i;
	size_t		len;

	num = (long int)n;
	i = 0;
	len = ft_len(num);
	if (!(str = malloc((sizeof(char) * (len + 1)))))
		return (NULL);
	str[len] = '\0';
	if (num == 0)
		str[0] = '0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		--len;
		str[len] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}
