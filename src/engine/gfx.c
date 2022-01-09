/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:01:10 by trobin            #+#    #+#             */
/*   Updated: 2022/01/05 17:36:34 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_wall_column(t_data *data)
{
	double			col;
	double			angle;
	t_double_vector	pos;
	t_image			*texture;

	angle = data->ray.angle;
	texture = data->wall.texture;
	pos = data->player.pos;
	if (texture == &data->images.est && angle < 0.5 * M_PI)
		col = pos.y + sin(angle) * data->ray.dist.x;
	else if (texture == &data->images.est && angle > 1.5 * M_PI)
		col = pos.y - sin(2 * M_PI - angle) * data->ray.dist.x;
	else if (texture == &data->images.west && angle < M_PI)
		col = pos.y + sin(M_PI - angle) * data->ray.dist.x;
	else if (texture == &data->images.west && angle > M_PI)
		col = pos.y - sin(angle - M_PI) * data->ray.dist.x;
	else if (texture == &data->images.north && angle < M_PI * 1.5)
		col = pos.x - sin(M_PI * 1.5 - angle) * data->ray.dist.y;
	else if (texture == &data->images.north && angle > M_PI * 1.5)
		col = pos.x + sin(angle - 1.5 * M_PI) * data->ray.dist.y;
	else if (texture == &data->images.south && angle < M_PI * 0.5)
		col = pos.x + sin(0.5 * M_PI - angle) * data->ray.dist.y;
	else
		col = pos.x - sin(angle - 0.5 * M_PI) * data->ray.dist.y;
	data->wall.column = (int)(col) % CUB_SIZE;
}

static void	get_wall_dist(t_data *data)
{
	double	fisheye_corrector;

	fisheye_corrector = cos(data->player.dir - data->ray.angle);
	data->wall.dist = fmin(data->ray.dist.x, data->ray.dist.y)
		* fisheye_corrector;
}

static void	get_wall_texture(t_data *data)
{
	if (data->ray.dist.x < data->ray.dist.y)
	{
		if (data->ray.angle > 0.5 * M_PI && data->ray.angle < 1.5 * M_PI)
			data->wall.texture = &data->images.west;
		else
			data->wall.texture = &data->images.est;
	}
	else
	{
		if (data->ray.angle > 0 && data->ray.angle < M_PI)
			data->wall.texture = &data->images.south;
		else
			data->wall.texture = &data->images.north;
	}
}

static void	get_wall_height(t_data *data)
{
	data->wall.height = (int)((double)CUB_SIZE / 2 / data->wall.dist
			* (double)WIN_SIZE / tan(data->player.fov / 2));
	if (data->wall.height > WIN_SIZE)
	{
		data->wall.lo = WIN_SIZE / 2 - data->wall.height / 2;
		data->wall.hi = WIN_SIZE;
	}
	else
	{
		data->wall.lo = WIN_SIZE / 2 - data->wall.height / 2;
		data->wall.hi = WIN_SIZE / 2 + data->wall.height / 2;
	}
}

void	textured_column_to_image(t_data *data)
{
	int	row;
	int	color;

	get_wall_dist(data);
	get_wall_texture(data);
	get_wall_height(data);
	get_wall_column(data);
	row = 0;
	while (row < data->wall.lo)
	{
		pixel_to_image(&data->images.cub3d, data->ray.column, row++,
			data->colors.ceiling.color);
	}
	while (row < data->wall.hi)
	{
		color = get_image_pixel_color(data->wall.texture, data->wall.column,
				(row - data->wall.lo) * CUB_SIZE / data->wall.height);
		pixel_to_image(&data->images.cub3d, data->ray.column, row++, color);
	}
	while (row < WIN_SIZE)
	{
		pixel_to_image(&data->images.cub3d, data->ray.column, row++,
			data->colors.floor.color);
	}
}
