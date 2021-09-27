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

#include "cub3d.h"

/*
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
*/

t_double_vector	get_delta(t_player *player)
{
	t_double_vector	delta;

	if (player->dir < 0.5 * M_PI) // SOUTH/WEST
	{
		// on a : cos(dir) = delta.x / MOVEMENT_UNIT
		// i.e. : delta.x = cos(dir) * MOVEMENT_UNIT
		delta.x = cos(player->dir) * MOVEMENT_UNIT;
		// on a : cos(0.5 * M_PI - dir) = delta.y / MOVEMENT_UNIT
		// i.e. : delta.y = cos(0.5 * M_PI - dir) * MOVEMENT_UNIT
		delta.y = cos(0.5 * M_PI - player->dir) * MOVEMENT_UNIT;
	}
	else if (player->dir < M_PI) // SOUTH/WEST
	{
		// on a : cos(M_PI - dir) = delta.x / MOVEMENT_UNIT
		// i.e. : delta.x = cos(M_PI - dir) * MOVEMENT_UNIT
		delta.x = cos(M_PI - player->dir) * MOVEMENT_UNIT;
		// on a : cos(dir - 0.5 * M_PI) = delta.y / MOVEMENT_UNIT
		// i.e. : delta.y = cos(dir - 0.5 * M_PI) * MOVEMENT_UNIT
		delta.y = cos(player->dir - 0.5 * M_PI) * MOVEMENT_UNIT;
	}
	else if (player->dir < 1.5 * M_PI) // NORTH/WEST
	{
		// on a : cos(dir - 0.5 * M_PI) = delta.x / MOVEMENT_UNIT
		// i.e. : delta.x = cos(dir - 0.5 * M_PI) * MOVEMENT_UNIT
		delta.x = cos(player->dir - 0.5 * M_PI) * MOVEMENT_UNIT;
		// on a : cos(1.5 * M_PI - dir) = delta.y / MOVEMENT_UNIT
		// i.e. : delta.y = cos(1.5 * M_PI - dir) * MOVEMENT_UNIT
		delta.y = cos(1.5 * M_PI - player->dir) * MOVEMENT_UNIT;
	}
	else
	{
		// on a : cos(2 * M_PI - dir) = delta.x / MOVEMENT_UNIT
		// i.e. : delta.x = cos(2 * M_PI - dir) * MOVEMENT_UNIT
		delta.x = cos(2 * M_PI - player->dir) * MOVEMENT_UNIT;
		// on a : cos(dir - 1.5 * M_PI) = delta.y / MOVEMENT_UNIT
		// i.e. : delta.y = cos(dir - 1.5 * M_PI) * MOVEMENT_UNIT
		delta.y = cos(player->dir - 1.5 * M_PI) * MOVEMENT_UNIT;
	}
//	player->map.x = (int)player->pos.x;
//	player->map.y = (int)player->pos.y;
	return (delta);
}

void	forward(t_data *data)
{
	t_double_vector delta;
       
	delta = get_delta(&data->player);
	printf("DELTA: [%f, %f]\n", delta.x, delta.y);
	printf("POS  : [%f, %f]\n", data->player.pos.x, data->player.pos.y);

	if (data->map[(int)(data->player.pos.x + delta.x)][(int)(data->player.pos.y + delta.y)] != '1')
	{
		printf("yo\n");
		data->player.pos.x += delta.x;
		data->player.pos.y += delta.y;
		data->player.map.x = (int)data->player.pos.x;
		data->player.map.y = (int)data->player.pos.y;
	}
}

int	key_hook(int key, t_data *data)
{
	printf("key: %d\n", key);
	if (key == ESC)
		mlx_loop_end(data->mlx_ptr);
	else if (key == W)
		forward(data);
//	else if (key == S)
//		backward(data);
//	else if (key == A)
//		left(data);
//	else if (key == D)
//		right(data);
	// update image
//	if (key == W || key == S || key == A || key == D)
//	{
//		print_game_data(&data->game);
//		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img.img, 0, 0);
//	}
	else if (key == RIGHT)
		rotate_player(&data->player, (double)ROTATION_UNIT);
	else if (key == LEFT)
		rotate_player(&data->player, (double)(ROTATION_UNIT * (-1)));
	else if (key == Z)
	{
		print_2d_array(data->map);
		print_player_data(&data->player);
		raycasting(data);
	//	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img.img, 0, 0);
	}
	return (1);
}
