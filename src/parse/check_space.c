/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:28:04 by trobin            #+#    #+#             */
/*   Updated: 2021/10/09 17:29:28 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_lower_cell(char **map, int row, int col)
{
	if (col >= ft_strlen(map[row + 1]))
		return (0);
	return (&map[row + 1][col]);
}

static char	*get_upper_cell(char **map, int row, int col)
{
	if (col >= ft_strlen(map[row - 1]))
		return (0);
	return (&map[row - 1][col]);
}

static char	*get_right_cell(char **map, int row, int col)
{
	if (col == ft_strlen(map[row]) - 1)
		return (0);
	return (&map[row][col + 1]);
}

static char	*get_left_cell(char **map, int row, int col)
{
	if (!col)
		return (0);
	return (&map[row][col - 1]);
}

void	check_space(t_data *data, char **map, int row, int col)
{
	char	*tmp;

	tmp = get_upper_cell(map, row, col);
	if (!tmp || *tmp == ' ')
		exit_cub3d(data, MAP_NOT_CLOSE);
	tmp = get_lower_cell(map, row, col);
	if (!tmp || *tmp == ' ')
		exit_cub3d(data, MAP_NOT_CLOSE);
	tmp = get_right_cell(map, row, col);
	if (!tmp || *tmp == ' ')
		exit_cub3d(data, MAP_NOT_CLOSE);
	tmp = get_left_cell(map, row, col);
	if (!tmp || *tmp == ' ')
		exit_cub3d(data, MAP_NOT_CLOSE);
}
