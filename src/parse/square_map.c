/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:18:46 by trobin            #+#    #+#             */
/*   Updated: 2021/09/23 12:20:45 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_max_len(char **map)
{
	int i;
	int max;
	int curr;

	i = 0;
	max = 0;
	while (map[i])
	{
		curr = ft_strlen(map[i]);
		if (curr > max)
			max = curr;
		++i;
	}
	return (max);
}

t_bool	square_map(char **map)
{
	int		max;
	int		curr;
	char	*tmp;

	if (!map)
		return (1);
	max = get_max_len(map);
	while (*map)
	{
		curr = ft_strlen(*map);
		if (curr < max)
		{
			tmp = 0;
			tmp = malloc(sizeof(char) * (max + 1));
			if (!tmp)
				return (0); // error malloc
			ft_memcpy(tmp, *map, curr);
			ft_memset(tmp + curr, ' ', max - curr);
			tmp[max] = '\0';
			free(*map);
			*map = tmp;
		}
		map++;
	}
	return (1);
}
