/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:17:40 by trobin            #+#    #+#             */
/*   Updated: 2021/10/11 18:39:15 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_int_vector	get_step(double ray)
{
	t_int_vector	step;

	if (ray < 0.5 * M_PI)
	{
		step.x = 1;
		step.y = 1;
	}
	else if (ray < M_PI)
	{
		step.x = -1;
		step.y = 1;
	}
	else if (ray < 1.5 * M_PI)
	{
		step.x = -1;
		step.y = -1;
	}
	else
	{
		step.x = 1;
		step.y = -1;
	}
	return (step);
}

static t_double_vector	get_delta_dist(double ray)
{
	t_double_vector	delta_dist;

	if (ray < 0.5 * M_PI)
	{
		delta_dist.x = CUB_SIZE / cos(ray);
		delta_dist.y = CUB_SIZE / cos(0.5 * M_PI - ray);
	}
	else if (ray < M_PI)
	{
		delta_dist.x = CUB_SIZE / cos(M_PI - ray);
		delta_dist.y = CUB_SIZE / cos(ray - 0.5 * M_PI);
	}
	else if (ray < 1.5 * M_PI)
	{
		delta_dist.x = CUB_SIZE / cos(ray - M_PI);
		delta_dist.y = CUB_SIZE / cos(1.5 * M_PI - ray);
	}
	else
	{
		delta_dist.x = CUB_SIZE / cos(2.0 * M_PI - ray);
		delta_dist.y = CUB_SIZE / cos(ray - 1.5 * M_PI);
	}
	return (delta_dist);
}

static t_double_vector	init_ray_dist(t_int_vector map, t_double_vector pos,
										double ray)
{
	t_double_vector	dist;

	if (ray < 0.5 * M_PI)
	{
		dist.y = ((map.y + 1) * CUB_SIZE - pos.y) / cos(0.5 * M_PI - ray);
		dist.x = ((map.x + 1) * CUB_SIZE - pos.x) / cos(ray);
	}
	else if (ray < M_PI)
	{
		dist.y = ((map.y + 1) * CUB_SIZE - pos.y) / cos(ray - 0.5 * M_PI);
		dist.x = (pos.x - map.x * CUB_SIZE) / cos(M_PI - ray);
	}
	else if (ray < 1.5 * M_PI)
	{
		dist.y = (pos.y - map.y * CUB_SIZE) / cos(1.5 * M_PI - ray);
		dist.x = (pos.x - map.x * CUB_SIZE) / cos(ray - M_PI);
	}
	else
	{
		dist.y = (pos.y - map.y * CUB_SIZE) / cos(ray - 1.5 * M_PI);
		dist.x = ((map.x + 1) * CUB_SIZE - pos.x) / cos(2.0 * M_PI - ray);
	}
	return (dist);
}

void	dda(t_data *data)
{
	data->ray.map = data->player.map;
	data->ray.step = get_step(data->ray.angle);
	data->ray.delta = get_delta_dist(data->ray.angle);
	data->ray.dist = init_ray_dist(
			data->player.map,
			data->player.pos,
			data->ray.angle);
	while (1)
	{
		if (data->ray.dist.x < data->ray.dist.y)
		{
			data->ray.map.x += data->ray.step.x;
			if (data->map[data->ray.map.y][data->ray.map.x] == '1')
				break ;
			data->ray.dist.x += data->ray.delta.x;
		}
		else
		{
			data->ray.map.y += data->ray.step.y;
			if (data->map[data->ray.map.y][data->ray.map.x] == '1')
				break ;
			data->ray.dist.y += data->ray.delta.y;
		}
	}
}

void	raycasting(t_data *data)
{
	data->ray.rot = (double)(data->player.fov / (double)WIN_SIZE);
	data->ray.angle = rotate(data->player.dir, data->player.fov / 2.0 * (-1.0));
	data->ray.column = 0;
	while (data->ray.column < WIN_SIZE)
	{
		dda(data);
		textured_column_to_image(data);
		data->ray.angle = rotate(data->ray.angle, data->ray.rot);
		data->ray.column++;
	}
}
