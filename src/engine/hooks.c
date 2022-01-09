/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:34:27 by trobin            #+#    #+#             */
/*   Updated: 2021/12/22 17:25:27 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	render(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->images.cub3d.img, 0, 0);
	return (0);
}

static int	key_hook(int key, t_data *data)
{
	if (key == ESC)
		mlx_loop_end(data->mlx);
	if (key == W)
		move(data, data->player.dir);
	else if (key == S)
		move(data, rotate(data->player.dir, M_PI));
	else if (key == A)
		move(data, rotate(data->player.dir, M_PI / 2 * (-1)));
	else if (key == D)
		move(data, rotate(data->player.dir, M_PI / 2));
	else if (key == RIGHT)
		rotate_player(&data->player, data->player.rot);
	else if (key == LEFT)
		rotate_player(&data->player, data->player.rot * (-1));
	else
		return (1);
	raycasting(data);
	return (0);
}

/*
 * cf. /usr/include/X11/X.h
 *
 * #define KeyPress			2
 * #define ClientMessage	17
 * #define KeyPressMask		(1L<<0)
 * #define GCClipXOrigin	(1L<<17)
 *
 */
void	define_hooks(t_data *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask, &key_hook, data);
	mlx_hook(data->win, ClientMessage, GCClipXOrigin, &mlx_loop_end, data->mlx);
	mlx_loop_hook(data->mlx, &render, (void *)data);
	mlx_loop(data->mlx);
}
