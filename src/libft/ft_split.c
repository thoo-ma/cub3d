/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:11:50 by trobin            #+#    #+#             */
/*   Updated: 2021/10/09 16:04:10 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_words(char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c)
			++i;
		if (!s[i])
			return (words);
		while (s[i] && s[i] != c)
			++i;
		++words;
	}
	return (words);
}

static int	ft_allocate_words(char **dest, char *s, char c, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] == c)
			++j;
		k = 0;
		while (s[j + k] && s[j + k] != c)
			++k;
		dest[i] = 0;
		dest[i] = malloc(sizeof(char) * (k + 1));
		if (!(dest[i]))
			return (0);
		ft_strcpy(dest[i], s + j, k + 1);
		j += k;
		++i;
	}
	dest[i] = 0;
	return (1);
}

static void	ft_free(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		++i;
	}
	free(to_free);
}

char	**ft_split(char *s, char c)
{
	char	**dest;
	int		words;

	if (!s)
		return (0);
	words = ft_get_words(s, c);
	dest = 0;
	dest = malloc(sizeof(char *) * (words + 1));
	if (!dest)
		return (0);
	if (!(ft_allocate_words(dest, s, c, words)))
	{
		ft_free(dest);
		return (0);
	}
	return (dest);
}
