/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:28:04 by trobin            #+#    #+#             */
/*   Updated: 2022/01/07 18:47:22 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_undefined_cells(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		if (ft_strcspn(data->map[i], " 01NSEW"))
			exit_cub3d(data, MAP_UNDEFINED);
		i++;
	}
}

static void	check_cardinal(t_data *data, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = elems_index(map[y], "NSEW");
		if (x > -1)
		{
			get_player_data(&data->player, x, y, map[y][x]);
			if (elems_index(map[y] + x + 1, "NSEW") > -1)
				exit_cub3d(data, MAP_MULT_CARDINALS);
			while (map[++y])
			{
				if (elems_index(map[y], "NSEW") > -1)
					exit_cub3d(data, MAP_MULT_CARDINALS);
			}
			return ;
		}
		y++;
	}
	exit_cub3d(data, MAP_NO_CARDINAL);
}

static void	check_map_closed(t_data *data, char **map)
{
	int	i;
	int	j;

	i = length_2d_array(map);
	if (ft_strcspn(map[0], " 1"))
		exit_cub3d(data, MAP_NOT_CLOSE);
	if (ft_strcspn(map[i - 1], " 1"))
		exit_cub3d(data, MAP_NOT_CLOSE);
	while (--i)
	{
		j = ft_strlen(map[i]) - 1;
		if (elem_index(" 1", map[i][0]) == -1
			|| elem_index(" 1", map[i][j]) == -1)
			exit_cub3d(data, MAP_NOT_CLOSE);
		while (--j)
		{
			if (map[i][j] == '0')
				check_space(data, map, i, j);
		}
	}
}

void	get_player_data(t_player *player, int x, int y, char c)
{
	player->map.x = x;
	player->map.y = y;
	player->pos.x = (double)CUB_SIZE * ((double)x + 1.0 / 3.0);
	player->pos.y = (double)CUB_SIZE * ((double)y + 1.0 / 3.0);
	if (c == 'W')
		player->dir = M_PI;
	else if (c == 'S')
		player->dir = M_PI / 2;
	else if (c == 'N')
		player->dir = 3 * M_PI / 2;
	else
		player->dir = 0;
}

void	check_map(t_data *data)
{
	if (data->map)
	{
		check_undefined_cells(data);
		check_cardinal(data, data->map);
		check_map_closed(data, data->map);
	}
}
