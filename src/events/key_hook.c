/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:30:23 by trobin            #+#    #+#             */
/*   Updated: 2021/09/23 18:02:31 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*		OLD
void	forward(t_data *data)
{
	double *dirx = &data->game.dir->x;
	double *diry = &data->game.dir->y;

	double *posx = &data->game.pos->x;
	double *posy = &data->game.pos->y;

	double old_posx = *posx;
	double old_posy = *posy;

	if ((int)*dirx > 0 && !is_wall(data->game.map, (int)(*posx + 1), (int)*posy))
		//(*posx)++;
		(*posx) += MOVEMENT_UNIT;
	else if ((int)*dirx < 0 && !is_wall(data->game.map, (int)(*posx - 1), (int)*posy))
		//(*posx)--;
		(*posx) -= MOVEMENT_UNIT;
	else if ((int)*diry > 0 && !is_wall(data->game.map, (int)*posx, (int)(*posy + 1)))
		//(*posy)++;
		(*posy) += MOVEMENT_UNIT;
	else if ((int)*diry < 0 && !is_wall(data->game.map, (int)*posx, (int)(*posy - 1)))
		//(*posy)--;
		(*posy) -= MOVEMENT_UNIT;
	if (old_posx != *posx || old_posy != *posy)
	//if (trunc(old_posx) != trunc(*posx) || trunc(old_posy) != trunc(*posy))
	{
		square_pixel_to_image(&data->mlx.img,
			(int)(trunc(*posx) * SQUARE_LENGTH),
			(int)(trunc(*posy) * SQUARE_LENGTH), BLUE);
		square_pixel_to_image(&data->mlx.img,
			(int)(trunc(old_posx) * SQUARE_LENGTH),
			(int)(trunc(old_posy) * SQUARE_LENGTH), GREEN);
	}
}

void	backward(t_data *data)
{
	double *dirx = &data->game.dir->x;
	double *diry = &data->game.dir->y;

	double *posx = &data->game.pos->x;
	double *posy = &data->game.pos->y;

	double old_posx = *posx;
	double old_posy = *posy;

	if ((int)*dirx > 0 && !is_wall(data->game.map, (int)(*posx - 1), (int)*posy))
		//(*posx)--;
		(*posx) -= MOVEMENT_UNIT;
	else if ((int)*dirx < 0 && !is_wall(data->game.map, (int)(*posx + 1), (int)*posy))
		//(*posx)++;
		(*posx) += MOVEMENT_UNIT;
	else if ((int)*diry > 0 && !is_wall(data->game.map, (int)*posx, (int)(*posy - 1)))
		//(*posy)--;
		(*posy) -= MOVEMENT_UNIT;
	else if ((int)*diry < 0 && !is_wall(data->game.map, (int)*posx, (int)(*posy + 1)))
		//(*posy)++;
		(*posy) += MOVEMENT_UNIT;

	//if (old_posx != *posx || old_posy != *posy)
	if (trunc(old_posx) != trunc(*posx) || trunc(old_posy) != trunc(*posy))
	{
		square_pixel_to_image(&data->mlx.img,
			(int)(*posx * SQUARE_LENGTH), (int)(*posy * SQUARE_LENGTH), BLUE);
		square_pixel_to_image(&data->mlx.img,
			(int)(old_posx * SQUARE_LENGTH), (int)(old_posy * SQUARE_LENGTH), GREEN);
	}
}

void	left_rotate(t_data *data)
{
	double old_dir_x;
	double old_dir_y;
	double old_plane_x;
	double old_plane_y;

	double new_dir_x;
	double new_dir_y;
	double new_plane_x;
	double new_plane_y;

	//double angle = 270 * M_PI / 180;
	double angle = (360.0 - ROTATION_UNIT) * M_PI / 180.0;

	// same assignation
	old_dir_x = data->game.dir->x;
	old_dir_y = data->game.dir->y;

	// same assignation
	old_plane_x = data->game.plane->x;
	old_plane_y = data->game.plane->y;

	// same calcul
	new_dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
	new_dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);

	// same calcul
	new_plane_x = old_plane_x * cos(angle) - old_plane_y * sin(angle);
	new_plane_y = old_plane_x * sin(angle) + old_plane_y * cos(angle);

	// same assignation bis
	data->game.dir->x = new_dir_x;
	data->game.dir->y = new_dir_y;

	// same assignation bis
	data->game.plane->x = new_plane_x;
	data->game.plane->y = new_plane_y;
}

void	right_rotate(t_data *data)
{
	double old_dir_x;
	double old_dir_y;
	double old_plane_x;
	double old_plane_y;

	double new_dir_x;
	double new_dir_y;
	double new_plane_x;
	double new_plane_y;

	//double angle = 90 * M_PI / 180;
	double angle = ROTATION_UNIT * M_PI / 180.0;

	// same assignation
	old_dir_x = data->game.dir->x;
	old_dir_y = data->game.dir->y;

	// same assignation
	old_plane_x = data->game.plane->x;
	old_plane_y = data->game.plane->y;

	// same calcul --> gotta use rotate(vector, angle)
	new_dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
	new_dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);

	// same calcul
	new_plane_x = old_plane_x * cos(angle) - old_plane_y * sin(angle);
	new_plane_y = old_plane_x * sin(angle) + old_plane_y * cos(angle);

	// same assignation bis
	data->game.dir->x = new_dir_x;
	data->game.dir->y = new_dir_y;

	// same assignation bis
	data->game.plane->x = new_plane_x;
	data->game.plane->y = new_plane_y;
}

int		key_hook(int key, t_data *data)
{
	printf("key: %d\n", key);

	// exit
	if (key == ESC)
		mlx_loop_end(data->mlx.mlx);

	// moove
	else if (key == W)
		forward(data);
	else if (key == S)
		backward(data);
	else if (key == A)
	{
//		erase_rays_from_image(&data->mlx.img,
//			&data->game.pos->x, &data->game.pos->y,
//			&data->game.dir->x, &data->game.dir->y, data->game.map);
		left_rotate(data);
	}
	else if (key == D)
	{
//		erase_rays_from_image(&data->mlx.img,
//			&data->game.pos->x, &data->game.pos->y,
//			&data->game.dir->x, &data->game.dir->y, data->game.map);
		right_rotate(data);
	}

	if (key == W || key == S || key == A || key == D)
	{
		print_game_data(&data->game);
//		raycasting(data);
//		rays_to_image(&data->mlx.img,
//			&data->game.pos->x, &data->game.pos->y,
//			&data->game.dir->x, &data->game.dir->y, data->game.map);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img.img,
			0, 0);
	}

	if (key == Z)
	{
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img.img,
		0, 0);
	}

	return (1);
}
*/

/*
//		NEW
void	forward(t_data *data)
{
	double dir = data->game.dir;

	double *posx = &data->game.pos->x;
	double *posy = &data->game.pos->y;

	double old_posx = *posx;
	double old_posy = *posy;

	int mapx = (int)(floor(*posx / SQUARE_LENGTH));
	int mapy = (int)(floor(*posy / SQUARE_LENGTH));

//	printf("__mapx = %d\n", mapx);
//	printf("__is there a wall in [%d][%d]\n", mapx + 1, mapy);
//	printf("__map[%d][%d] = '%c'\n", mapx + 1, mapy, data->game.map[mapy][mapx + 1]);

	// merge `is_wall()` and third condition into another function ? (array of function pointers ?...)
	if (dir == 0 && (!is_wall(data->game.map, mapx + 1, mapy) || MOVEMENT_UNIT <= (int)((mapx + 1) * SQUARE_LENGTH - *posx - 1)))
		*posx += MOVEMENT_UNIT;
	if (dir == 180 && (!is_wall(data->game.map, mapx - 1, mapy) || MOVEMENT_UNIT <= (int)(*posx - mapx * SQUARE_LENGTH)))
		*posx -= MOVEMENT_UNIT;
	if (dir == 90 && (!is_wall(data->game.map, mapx, mapy + 1) || MOVEMENT_UNIT <= (int)((mapy + 1) * SQUARE_LENGTH - *posy - 1)))
		*posy += MOVEMENT_UNIT;
	if (dir == 270 && (!is_wall(data->game.map, mapx, mapy - 1) || MOVEMENT_UNIT <= (int)(*posy - mapy * SQUARE_LENGTH)))
		*posy -= MOVEMENT_UNIT;

//	printf("old_pos | [%d, %d]\n", (int)old_posx, (int)old_posy);
//	printf("new_pos | [%d, %d]\n", (int)*posx, (int)*posy);

	if (old_posx != *posx || old_posy != *posy)
	{
		pixel_to_image(&data->mlx.img, (int)old_posy, (int)old_posx, GREEN);
		pixel_to_image(&data->mlx.img, (int)*posy, (int)*posx, BLUE);
	}
}

void	backward(t_data *data)
{
	double dir = data->game.dir;
	double *posx = &data->game.pos->x;
	double *posy = &data->game.pos->y;
	double old_posx = *posx;
	double old_posy = *posy;
	int mapx = (int)(floor(*posx / SQUARE_LENGTH));
	int mapy = (int)(floor(*posy / SQUARE_LENGTH));

	if (dir == 0 && (!is_wall(data->game.map, mapx - 1, mapy)
		|| MOVEMENT_UNIT <= (int)(*posx - mapx * SQUARE_LENGTH)))
		*posx -= MOVEMENT_UNIT;
	if (dir == 180 && (!is_wall(data->game.map, mapx + 1, mapy)
		|| MOVEMENT_UNIT <= (int)((mapx + 1) * SQUARE_LENGTH - *posx - 1)))
		*posx += MOVEMENT_UNIT;
	if (dir == 90 && (!is_wall(data->game.map, mapx, mapy - 1)
		|| MOVEMENT_UNIT <= (int)(*posy - mapy * SQUARE_LENGTH)))
		*posy -= MOVEMENT_UNIT;
	if (dir == 270 && (!is_wall(data->game.map, mapx, mapy + 1)
		|| MOVEMENT_UNIT <= (int)((mapy + 1) * SQUARE_LENGTH - *posy - 1)))
		*posy += MOVEMENT_UNIT;
	if (old_posx != *posx || old_posy != *posy)
	{
		pixel_to_image(&data->mlx.img, (int)old_posy, (int)old_posx, GREEN);
		pixel_to_image(&data->mlx.img, (int)*posy, (int)*posx, BLUE);
	}
}

//		remplacer par rotate() ? --> cf. src/verify/is_cardinal_valid.c
void	left_rotate(t_data *data)
{
	double *dir = &data->game.dir;

	// 4 directions : ROTATION_UNIT = 90
	if (*dir == 0)
		*dir = 3 * M_PI / 2;
	else if (*dir == M_PI / 2)
		*dir = 0;
	else if (*dir == M_PI)
		*dir = M_PI / 2;
	else if (*dir == 3 * M_PI / 2)
		*dir = M_PI;

	// All directions
//	if (dir < ROTATION_UNIT)
//		dir = 2 * M_PI - ROTATION_UNIT + dir;
//	else
//		dir -= ROTATION_UNIT;
}

//		remplacer par rotate() ? --> cf. src/verify/is_cardinal_valid.c
void	right_rotate(t_data *data)
{
	double *dir = &data->game.dir;

	// 4 directions : ROTATION_UNIT = 90
	if (*dir == 0)
		*dir = M_PI / 2;
	else if (*dir == M_PI / 2)
		*dir = M_PI;
	else if (*dir == M_PI)
		*dir = 3 * M_PI / 2;
	else if (*dir == 3 * M_PI / 2)
		*dir = 0;

	// All directions
	//if (*dir > 2 * M_PI - ROTATION_UNIT)
	//	*dir = *dir + ROTATION_UNIT - 2 * M_PI;
	//else
	//	*dir += ROTATION_UNIT;
}
*/

int		key_hook(int key, t_data *data)
{
	printf("key: %d\n", key);

	// exit
	if (key == ESC)
		mlx_loop_end(data->mlx_ptr);

	// moove
//	else if (key == W)
//		forward(data);
//	else if (key == S)
//		backward(data);
//	else if (key == A)
//		left_rotate(data);
//	else if (key == D)
//		right_rotate(data);

	// update image
//	if (key == W || key == S || key == A || key == D)
//	{
//		print_game_data(&data->game);
//		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img.img, 0, 0);
//	}
	
	if (key == Z)
	{
		print_player_data(&data->player);
		raycasting(data);
	//	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img.img, 0, 0);
	}

	return (1);
}
