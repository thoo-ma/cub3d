/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:04:28 by trobin            #+#    #+#             */
/*   Updated: 2021/10/11 19:04:59 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_mlx_instance(t_data *data)
{
	data->mlx = 0;
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_cub3d(data, MLX_INIT);
}

void	get_mlx_window(t_data *data)
{
	data->win = 0;
	data->win = mlx_new_window(data->mlx, WIN_SIZE, WIN_SIZE, "cub3D");
	if (!data->win)
		exit_cub3d(data, MLX_WINDOW);
}

void	get_mlx_image(t_data *data)
{
	data->images.cub3d.img = mlx_new_image(data->mlx, WIN_SIZE, WIN_SIZE);
	if (!data->images.cub3d.img)
		exit_cub3d(data, MLX_NEW_IMAGE);
	data->images.cub3d.addr = (int *)mlx_get_data_addr(
			data->images.cub3d.img,
			&data->images.cub3d.bpp,
			&data->images.cub3d.ll,
			&data->images.cub3d.endian);
}
