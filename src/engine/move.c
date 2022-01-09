/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:30:23 by trobin            #+#    #+#             */
/*   Updated: 2021/10/11 18:40:21 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_double_vector	get_delta_move(double dir, double movement_unit)
{
	t_double_vector	delta;

	if (dir < 0.5 * M_PI)
	{
		delta.x = cos(dir) * movement_unit;
		delta.y = cos(0.5 * M_PI - dir) * movement_unit;
	}
	else if (dir < M_PI)
	{
		delta.x = cos(M_PI - dir) * MOVEMENT_UNIT;
		delta.y = cos(dir - 0.5 * M_PI) * MOVEMENT_UNIT;
	}
	else if (dir < 1.5 * M_PI)
	{
		delta.x = cos(dir - M_PI) * movement_unit;
		delta.y = cos(1.5 * M_PI - dir) * movement_unit;
	}
	else
	{
		delta.x = cos(2.0 * M_PI - dir) * movement_unit;
		delta.y = cos(dir - 1.5 * M_PI) * movement_unit;
	}
	return (delta);
}

static inline double	get_move_dist(t_double_vector delta)
{
	return (sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

void	move(t_data *data, double dir)
{
	double			dist;
	double			wall;
	t_int_vector	step;
	t_double_vector	delta;

	step = get_step(dir);
	delta = get_delta_move(dir, data->player.mov);
	dist = get_move_dist(delta);
	data->ray.angle = dir;
	dda(data);
	wall = fmin(data->ray.dist.x, data->ray.dist.y);
	if (dist < wall
		&& data->map[(int)((data->player.pos.y + delta.y * step.y) / CUB_SIZE)]
		[(int)((data->player.pos.x + delta.x * step.x) / CUB_SIZE)] != '1')
	{
		data->player.pos.x += delta.x * step.x;
		data->player.pos.y += delta.y * step.y;
		data->player.map.x = (int)(data->player.pos.x / CUB_SIZE);
		data->player.map.y = (int)(data->player.pos.y / CUB_SIZE);
	}
}
