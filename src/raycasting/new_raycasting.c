/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:56:33 by trobin            #+#    #+#             */
/*   Updated: 2021/09/25 15:02:38 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//				GET_STEP
t_int_vector	get_step(double ray)
{
	t_int_vector step;

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

//				GET_ANGLE
t_double_vector		get_angle(double ray)
{
	double		i;
	t_double_vector	angle;

	i = 0;
	while (i < ray)
		i += M_PI / 2;

	angle.x = ray - i - M_PI / 2;
	angle.y = i - ray;

	return (angle);
}

//				INIT_DIST
/*
double			init_dist_ns(t_double_vector pos, double angle, double stepx, t_data *data)
{
	double ray;
	double delta_x; 
	double delta_y;
	double dist_ns;
	
	ray = data->player.dir;
	if (ray > M_PI && ray < M_PI * 2) // NORTH
	{
		delta_y = pos.y - floor(pos.y / SQUARE_LENGTH) * SQUARE_LENGTH; // * stepy ?
		dist_ns = delta_y / cos(angle);
		delta_x = dist_ns * sin(angle) * stepx;
	}
	else // SOUTH
	{
		delta_y = SQUARE_LENGTH * (floor)(pos.y / SQUARE_LENGTH + 1) - pos.y;
		dist_ns = delta_y / cos(angle);
		delta_x = dist_ns * sin(angle) * stepx;
	}
	return (dist_ns);
}

double			init_dist_ew(t_double_vector pos, double angle, double stepy, t_data *data)
{
	double ray;
	double delta_x; 
	double delta_y;
	double dist_ew;
	
	ray = data->player.dir;
	if (ray > 0.5 * M_PI && ray < 1.5 * M_PI) // WEST
	{
		delta_x = pos.x - floor(pos.x / SQUARE_LENGTH) * SQUARE_LENGTH;// * stepx ?
		dist_ew = delta_x / cos(angle);
		delta_y = dist_ew * sin(angle) * stepy;
	}
	else // EST
	{
		delta_x = floor(pos.x / SQUARE_LENGTH) * SQUARE_LENGTH - pos.x;
		dist_ew = delta_x / cos(angle);
		delta_y = dist_ew * sin(angle) * stepy;
	}
	return (dist_ew);
}
*/

t_double_vector		old_init_dist(t_double_vector pos, double ray)
{
	t_double_vector dist;
	
	if (ray < 0.5 * M_PI) // SOUTH/EST
	{
		// ON A : dist_ns = delta_y / cos(angle);
		// OR   : delta_y = SQUARE_LENGTH * (floor)(pos.y / SQUARE_LENGTH + 1) - pos.y;
		// ET   : angle	  = 0.5 * M_PI - ray;
		// D'OU : dist_ns = (SQUARE_LENGTH * (floor)(pos.y / SQUARE_LENGTH + 1) - pos.y) / cos(0.5 * M_PI - ray);
		dist.y = (SQUARE_LENGTH * (floor)(pos.y / SQUARE_LENGTH + 1) - pos.y) / cos(0.5 * M_PI - ray);

		// ON A : dist_ew = delta_x / cos(angle);
		// OR   : delta_x = floor(pos.x / SQUARE_LENGTH + 1) * SQUARE_LENGTH - pos.x;
		// ET   : angle   = ray;
		// D'OU : dist_ew = (floor(pos.x / SQUARE_LENGTH + 1) * SQUARE_LENGTH - pos.x) / cos(ray);
		dist.x = (floor(pos.x / SQUARE_LENGTH + 1) * SQUARE_LENGTH - pos.x) / cos(ray);
	}
	else if (ray < M_PI) // SOUTH/WEST
	{
		// ON A : dist_ns = delta_y / cos(angle);
		// OR   : delta_y = SQUARE_LENGTH * (floor)(pos.y / SQUARE_LENGTH + 1) - pos.y;
		// ET   : angle   = ray - 0.5 * M_PI;
		// D'OU : dist_ns = (SQUARE_LENGTH * (floor)(pos.y / SQUARE_LENGTH + 1) - pos.y) / cos(ray - 0.5 * M_PI);
		dist.y = (SQUARE_LENGTH * (floor)(pos.y / SQUARE_LENGTH + 1) - pos.y) / cos(ray - 0.5 * M_PI);

		// ON A : dist_ew = delta_x / cos(angle);
		// OR   : delta_x = pos.x - floor(pos.x / SQUARE_LENGTH) * SQUARE_LENGTH;
		// ET   : angle   = M_PI - ray;
		// D'OU : dist_ew = (pos.x - floor(pos.x / SQUARE_LENGTH) * SQUARE_LENGTH) / cos(M_PI - ray);
		dist.x = (pos.x - floor(pos.x / SQUARE_LENGTH) * SQUARE_LENGTH) / cos(M_PI - ray);
	}
	else if (ray < 1.5 * M_PI) // NORTH/WEST
	{
		// ON A : dist_ns = delta_y / cos(angle);
		// OR   : delta_y = pos.y - floor(pos.y / SQUARE_LENGTH) * SQUARE_LENGTH;
		// ET   : angle   = 1.5 * M_PI - ray;
		// D'OU : dist_ns = (pos.y - floor(pos.y / SQUARE_LENGTH) * SQUARE_LENGTH) / cos(1.5 * M_PI - ray);
		dist.y = (pos.y - floor(pos.y / SQUARE_LENGTH) * SQUARE_LENGTH) / cos(1.5 * M_PI - ray);

		// ON A : dist_ew = delta_x / cos(angle);
		// OR   : delta_x = pos.x - floor(pos.x / SQUARE_LENGTH) * SQUARE_LENGTH;
		// ET   : angle   = ray - M_PI;
		// D'OU : dist_ew = (pos.x - floor(pos.x / SQUARE_LENGTH) * SQUARE_LENGTH) / cos(ray - M_PI);
		dist.x = (pos.x - floor(pos.x / SQUARE_LENGTH) * SQUARE_LENGTH) / cos(ray - M_PI);
	}
	else // NORTH/EST
	{
		// ON A : dist_ns = delta_y / cos(angle);
		// OR   : delta_y = pos.y - floor(pos.y / SQUARE_LENGTH) * SQUARE_LENGTH;
		// ET   : angle   = ray - 1.5 * M_PI;
		// D'OU : dist_ns = (pos.y - floor(pos.y / SQUARE_LENGTH) * SQUARE_LENGTH) / cos(ray - 1.5 * M_PI);
		dist.y = (pos.y - floor(pos.y / SQUARE_LENGTH) * SQUARE_LENGTH) / cos(ray - 1.5 * M_PI);

		// ON A : dist_ew = delta_x / cos(angle);
		// OR   : delta_x = floor(pos.x / SQUARE_LENGTH + 1) * SQUARE_LENGTH - pos.x;
		// ET   : angle   = 2.0 * M_PI - ray;
		// D'OU : dist_ew = (floor(pos.x / SQUARE_LENGTH + 1) * SQUARE_LENGTH - pos.x) / cos(2.0 * M_PI - ray);
		dist.x = (floor(pos.x / SQUARE_LENGTH + 1) * SQUARE_LENGTH - pos.x) / cos(2.0 * M_PI - ray);

	}
	return (dist);
}

//				GET_DELTA_DIST
/*
double			get_delta_dist_ns(double angle, t_int_vector step)
{
	double delta_dist_y = SQUARE_LENGTH * step.y;
	double delta_dist_ns = delta_dist_y / cos(angle);
	double delta_dist_x = delta_dist_ns * sin(angle) * step.x;

	return (delta_dist_ns);
}

double			get_delta_dist_ew(double angle, t_int_vector step)
{
	double delta_dist_x = SQUARE_LENGTH * step.x;
	double delta_dist_ew = delta_dist_x / cos(angle);
	double delta_dist_y = delta_dist_ew * sin(angle) * step.y;

	return (delta_dist_ew);
}

double			get_delta_dist_n(double angle, double stepx)
{
	double delta_dist_y = SQUARE_LENGTH;// * stepy ? (* -1)
	double delta_dist_n = delta_dist_y / cos(angle);
	double delta_dist_x = delta_dist_n * sin(angle) * stepx;

	return (delta_dist_n);
}

double			get_delta_dist_s(double angle, double stepx)
{
	double delta_dist_y = SQUARE_LENGTH;
	double delta_dist_s = delta_dist_y / cos(angle);
	double delta_dist_x = delta_dist_s * sin(angle) * stepx;

	return (delta_dist_s);
}

double			get_delta_dist_w(double angle, double stepy)
{
	double delta_dist_x = SQUARE_LENGTH; // * stepx ?
	double delta_dist_w = delta_dist_x / cos(angle);
	double delta_dist_y = delta_dist_w * sin(angle) * stepy;

	return (delta_dist_w);
}

double			get_delta_dist_e(double angle, double stepy)
{
	double delta_dist_x = SQUARE_LENGTH;
	double delta_dist_e = delta_dist_x / cos(angle);
	double delta_dist_y = delta_dist_e * sin(angle) * stepy;

	return (delta_dist_e);
}
*/

t_double_vector		get_delta_dist(double ray)
{
	t_double_vector delta_dist;

	if (ray < 0.5 * M_PI) // SOUTH/EST
	{
		delta_dist.x = SQUARE_LENGTH / cos(ray);
		delta_dist.y = SQUARE_LENGTH / cos(0.5 * M_PI - ray);
	}
	else if (ray < M_PI) // SOUTH/WEST
	{
		delta_dist.x = SQUARE_LENGTH / cos(M_PI - ray);
		delta_dist.y = SQUARE_LENGTH / cos(ray - 0.5 * M_PI);
	}
	else if (ray < 1.5 * M_PI) // NORTH/WEST
	{
		delta_dist.x = SQUARE_LENGTH / cos(ray - M_PI);
		delta_dist.y = SQUARE_LENGTH / cos(1.5 * M_PI - ray);
	}
	else // NORTH/EST
	{
		delta_dist.x = SQUARE_LENGTH / cos(2.0 * M_PI - ray);
		delta_dist.y = SQUARE_LENGTH / cos(ray - 1.5 * M_PI);
	}
	return (delta_dist);
}

t_double_vector	init_dist(t_double_vector pos, t_int_vector map, double ray)
{
	t_double_vector dist;
	
	if (ray < 0.5 * M_PI) // SOUTH/EST
	{
		// ON A : dist_ns = delta_y / cos(angle);
		// OR   : delta_y = (map.y + 1) * SQUARE_LENGTH - pos.y;
		// ET   : angle	  = 0.5 * M_PI - ray;
		// D'OU : dist_ns = ((map.y + 1) * SQUARE_LENGTH - pos.y) / cos(0.5 * M_PI - ray);
		dist.y = ((map.y + 1) * SQUARE_LENGTH - pos.y) / cos(0.5 * M_PI - ray);

		// ON A : dist_ew = delta_x / cos(angle);
		// OR   : delta_x = (map.x + 1) * SQUARE_LENGTH - pos.x;
		// ET   : angle   = ray;
		// D'OU : dist_ew = ((map.x + 1) * SQUARE_LENGTH - pos.x) / cos(ray);
		dist.x = ((map.x + 1) * SQUARE_LENGTH - pos.x) / cos(ray);
	}
	else if (ray < M_PI) // SOUTH/WEST
	{
		// ON A : dist_ns = delta_y / cos(angle);
		// OR   : delta_y = (map.y + 1) * SQUARE_LENGTH - pos.y;
		// ET   : angle   = ray - 0.5 * M_PI;
		// D'OU : dist_ns = ((map.y + 1) * SQUARE_LENGTH - pos.y) / cos(ray - 0.5 * M_PI);
		dist.y = ((map.y + 1) * SQUARE_LENGTH - pos.y) / cos(ray - 0.5 * M_PI);

		// ON A : dist_ew = delta_x / cos(angle);
		// OR   : delta_x = (map.x + 1) * SQUARE_LENGTH - pos.x;
		// ET   : angle   = M_PI - ray;
		// D'OU : dist_ew = ((map.x + 1) * SQUARE_LENGTH) / cos(M_PI - ray);
		dist.x = ((map.x + 1) * SQUARE_LENGTH) / cos(M_PI - ray);
	}
	else if (ray < 1.5 * M_PI) // NORTH/WEST
	{
		// ON A : dist_ns = delta_y / cos(angle);
		// OR   : delta_y = pos.y - map.y * SQUARE_LENGTH;
		// ET   : angle   = 1.5 * M_PI - ray;
		// D'OU : dist_ns = (pos.y - map.y * SQUARE_LENGTH) / cos(1.5 * M_PI - ray);
		dist.y = (pos.y - map.y * SQUARE_LENGTH) / cos(1.5 * M_PI - ray);

		// ON A : dist_ew = delta_x / cos(angle);
		// OR   : delta_x = pos.x - map.x * SQUARE_LENGTH;
		// ET   : angle   = ray - M_PI;
		// D'OU : dist_ew = (pos.x - map.x * SQUARE_LENGTH) / cos(ray - M_PI);
		dist.x = (pos.x - map.x * SQUARE_LENGTH) / cos(ray - M_PI);
	}
	else // NORTH/EST
	{
		// ON A : dist_ns = delta_y / cos(angle);
		// OR   : delta_y = pos.y - map.y * SQUARE_LENGTH;
		// ET   : angle   = ray - 1.5 * M_PI;
		// D'OU : dist_ns = (pos.y - map.y * SQUARE_LENGTH) / cos(ray - 1.5 * M_PI);
		dist.y = (pos.y - map.y * SQUARE_LENGTH) / cos(ray - 1.5 * M_PI);

		// ON A : dist_ew = delta_x / cos(angle);
		// OR   : delta_x = (map.x + 1) * SQUARE_LENGTH - pos.x;
		// ET   : angle   = 2.0 * M_PI - ray;
		// D'OU : dist_ew = ((map.x + 1) * SQUARE_LENGTH - pos.x) / cos(2.0 * M_PI - ray);
		dist.x = ((map.x + 1) * SQUARE_LENGTH - pos.x) / cos(2.0 * M_PI - ray);

	}
	return (dist);
}

void			dda(t_data *data, double ray)
{
	t_double_vector		dist;
	t_double_vector		delta_dist;
	t_int_vector		step;
	t_int_vector		cell;
	
	dist = init_dist(data->player.pos, data->player.map, ray);
	//printf("init_dist: [%f;%f]\n", dist.x, dist.y);

	delta_dist = get_delta_dist(ray);
	printf("delta_dist: [%f;%f]\n", delta_dist.x, delta_dist.y);

	step = get_step(ray);
	//printf("step: [%d;%d]\n", step.x, step.y);

	cell = data->player.map;

	//int side;
	while (1)
	{
		printf("dist: [%f;%f]\n", dist.x, dist.y);
		printf("cell: [%d;%d]\n", cell.x, cell.y);
		if (dist.x < dist.y)
		{
			dist.x += delta_dist.x;
			cell.x += step.x;
		//	side = 0;
		}
		else
		{
			dist.y += delta_dist.y;
			cell.y += step.y;
		//	side = 1;
		}
		//if (data->map[cell.y][cell.x] > '0')
		if (data->map[cell.y][cell.x] == '1')
			break ;
	}
	printf("wall encountered in [%d;%d]\n", cell.x, cell.y);
	printf("final_dist: [%f;%f]\n", dist.x, dist.y);
	// get_wall_size(dist);
}

void	raycasting(t_data *data)
{
	double	ray;
	double	max;
	double	rot;

	ray = rotate(data->player.dir, FOV_RAD / 2 * (-1));
	max = rotate(data->player.dir, FOV_RAD / 2);
	rot = FOV_RAD / WIN_X;

	printf("ray: %f\n", ray);
	printf("max: %f\n", max);
	printf("rot: %f\n", rot);

	dda(data, data->player.dir);
//	while (ray < max)
//	{
//		dda(data, ray);
//		ray += rot;
//	}
}
