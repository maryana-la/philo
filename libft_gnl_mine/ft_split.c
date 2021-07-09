/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:31:44 by rchelsea          #+#    #+#             */
/*   Updated: 2020/11/24 20:35:26 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	if (!(*s))
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_word_len(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	**ft_free_split(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != '\0')
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**arr;

	i = 0;
	if (!s || (!(arr = malloc(sizeof(char *) * (ft_count_words(s, c) + 1)))))
		return (NULL);
	j = 0;
	while (j != ft_count_words(s, c))
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (!(arr[j] = malloc(sizeof(char) * (ft_word_len(&s[i], c) + 1))))
			return (ft_free_split(arr));
		arr[j][ft_word_len(&s[i], c)] = '\0';
		k = 0;
		while (s[i] != c && s[i] != '\0')
			arr[j][k++] = s[i++];
		j++;
	}
	arr[j] = NULL;
	return (arr);
}
