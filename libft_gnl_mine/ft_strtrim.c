/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:40:25 by rchelsea          #+#    #+#             */
/*   Updated: 2020/11/24 01:48:58 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check(const char *basic, char letter)
{
	size_t	i;

	i = 0;
	while (basic[i] != '\0' && basic[i] != letter)
		i++;
	if (basic[i] == letter)
		return (1);
	else
		return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		i;
	int		len_s1;

	if (!s1)
		return (0);
	len_s1 = ft_strlen(s1) - 1;
	i = 0;
	while (s1[i] != '\0' && check(set, s1[i]) == 1)
		i++;
	while (len_s1 >= 0 && check(set, s1[len_s1]) == 1)
		len_s1--;
	if (len_s1 < i)
		return (ft_substr(s1, i, len_s1));
	new = ft_substr(s1, i, (len_s1 - i + 1));
	return (new);
}
