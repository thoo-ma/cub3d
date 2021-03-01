/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:28:04 by trobin            #+#    #+#             */
/*   Updated: 2021/09/24 18:34:57 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*get_lower_cell(char **map, int row, int col)
{
	if (ft_strlen(map[row + 1]) < ft_strlen(map[row]))
		return (0);
	return (&map[row + 1][col]);
}

char	*get_upper_cell(char **map, int row, int col)
{
	if (ft_strlen(map[row - 1]) < ft_strlen(map[row]))
		return (0);
	return (&map[row - 1][col]);
}

char	*get_right_cell(char **map, int row, int col)
{
	if (col == ft_strlen(map[row]) - 1)
		return (0);
	return (&map[row][col + 1]);
}

char	*get_left_cell(char **map, int row, int col)
{
	if (!col)
		return (0);
	return (&map[row][col - 1]);
}

void	check_undefined_cells(t_data *data)
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

int		elems_index(char *s1, char *s2)
{
	int	i;
	int	index;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i])
		{
			index = elem_index(s2, s1[i]);
			if (index > -1)
				return (elem_index(s1, s2[index]));
			i++;
		}
	}
	return (-1);
}

void	get_player_data(t_player *player, int x, int y, char c)
{
	player->map.x = x;
	player->map.y = y;
	player->pos.x = (double)x * (double)SQUARE_LENGTH + (double)SQUARE_LENGTH / 2;
	player->pos.y = (double)y * (double)SQUARE_LENGTH + (double)SQUARE_LENGTH / 2;
	//player->pos.x = (double)(SQUARE_LENGTH * (x + 1 / 2));
	//player->pos.y = (double)(SQUARE_LENGTH * (y + 1 / 2));
	if (c == 'W')
	{
		player->dir = M_PI;
		player->plane = 3 * M_PI / 2;
	}
	else if (c == 'S')
	{
		player->dir = M_PI / 2;
		player->plane = M_PI;
	}
	else if (c == 'N')
	{
		player->dir = 3 * M_PI / 2;
		player->plane = 0;
	}
	else
	{
		player->dir = 0;
		player->plane = M_PI / 2;
	}
}

void	check_cardinal(t_data *data, char **map)
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
			if (elems_index(map[y] + x + 2, "NSEW") > -1)
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

void	check_space(t_data *data, char **map, int row, int col)
{
	char *tmp;

	tmp = get_upper_cell(map, row, col);
	if (tmp && !(*tmp == '1' || *tmp == ' '))
		exit_cub3d(data, MAP_NOT_CLOSE);
	tmp = get_lower_cell(map, row, col);
	if (tmp && !(*tmp == '1' || *tmp == ' '))
		exit_cub3d(data, MAP_NOT_CLOSE);
	tmp = get_right_cell(map, row, col);
	if (tmp && !(*tmp == '1' || *tmp == ' '))
		exit_cub3d(data, MAP_NOT_CLOSE);
	tmp = get_left_cell(map, row, col);
	if (tmp && !(*tmp == '1' || *tmp == ' '))
		exit_cub3d(data, MAP_NOT_CLOSE);
}

void	check_map_closed(t_data *data, char **map)
{
	int i;
	int j;
	
	i = length_2d_array(map);
	//printf("i=%d\n", i);
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
			if (map[i][j] == ' ')
				check_space(data, map, i, j);
		}
	}
}

void	check_map(t_data *data)
{
	if (data->map)
	{
		check_undefined_cells(data);
		check_cardinal(data, data->map);
		check_map_closed(data, data->map);
		// square_map()
	}
}
