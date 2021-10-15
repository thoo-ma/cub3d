/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:34:27 by trobin            #+#    #+#             */
/*   Updated: 2021/10/15 13:52:59 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	render(void *data)
{
	t_data	*d;

	d = (t_data *)data;
	mlx_put_image_to_window(d->mlx, d->win, d->images.cub3d.img, 0, 0);
	return (0);
}

static int	key_hook(int key, t_data *data)
{
	if (key == ESC)
		mlx_loop_end(data->mlx);
	if (key == W)
		forward(data);
	else if (key == S)
		backward(data);
	else if (key == A)
		left(data);
	else if (key == D)
		right(data);
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
