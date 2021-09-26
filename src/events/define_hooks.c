/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:34:27 by trobin            #+#    #+#             */
/*   Updated: 2021/09/23 14:01:07 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * cf. /usr/include/X11/X.h
 *
 * #define KeyRelease		3
 * #define ClientMessage	17
 * #define KeyReleaseMask	(1L<<1)
 * #define GCClipXOrigin	(1L<<17)
 *
 */
void	define_hooks(t_data *data)
{
//	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &key_hook, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, &key_hook, data);
	mlx_hook(data->win, ClientMessage, GCClipXOrigin, &mlx_loop_end, data->mlx_ptr);
	mlx_loop_hook(data->mlx_ptr, &do_nothing, (void *)0);
//	mlx_loop_hook(data->mlx_ptr, &mlx_put_image_to_window, (void *)data);
	mlx_loop(data->mlx_ptr);
}
