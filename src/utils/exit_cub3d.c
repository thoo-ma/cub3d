/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 07:33:13 by trobin            #+#    #+#             */
/*   Updated: 2021/10/09 17:35:28 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_cub3d(t_data *data)
{
	if (data)
	{
		if (data->map)
			free_2d_array(data->map);
		if (data->images.est.img)
			mlx_destroy_image(data->mlx, data->images.est.img);
		if (data->images.west.img)
			mlx_destroy_image(data->mlx, data->images.west.img);
		if (data->images.north.img)
			mlx_destroy_image(data->mlx, data->images.north.img);
		if (data->images.south.img)
			mlx_destroy_image(data->mlx, data->images.south.img);
		if (data->images.cub3d.img)
			mlx_destroy_image(data->mlx, data->images.cub3d.img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
	}
}

void	exit_cub3d(t_data *data, int my_errno)
{
	destroy_cub3d(data);
	if (my_errno)
	{
		write(2, "Error : ", 8);
		write(2, data->my_strerror[my_errno],
			ft_strlen(data->my_strerror[my_errno]));
		write(2, "\n", 1);
	}
	exit(my_errno);
}
