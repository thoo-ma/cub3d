/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 07:33:13 by trobin            #+#    #+#             */
/*   Updated: 2021/09/23 13:34:26 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
void	free_game_data(t_game_data *data)
{
	if (data->map)
		free_2d_array(data->map);
	if (data->resolution)
		free(data->resolution);
	if (data->ceiling)
		free(data->ceiling);
	if (data->floor)
		free(data->floor);
	if (data->north)
		free(data->north);
	if (data->south)
		free(data->south);
	if (data->est)
		free(data->est);
	if (data->west)
		free(data->west);
	if (data->sprite)
		free(data->sprite);
	if (data->pos)
		free(data->pos);
}

void	free_mlx_data(t_mlx_data *mlx)
{
	if (mlx->img.img)
	{
		mlx_destroy_image(mlx->mlx, mlx->img.img);
		printf("image destroyed\n");
	}
	if (mlx->win)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		printf("window destroyed\n");
	}
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		printf("display destroyed\n");
	}
	if (mlx->mlx)
	{
		free(mlx->mlx);
		printf("mlx ptr freed\n");
	}
	//printf("free_mlx_data() : DONE\n");
}
*/

void	destroy_cub3d(t_data *data)
{
	if (data)
	{
		if (data->map)
			free_2d_array(data->map);
		if (data->images.est.img)
			mlx_destroy_image(data->mlx_ptr, data->images.est.img);
		if (data->images.west.img)
			mlx_destroy_image(data->mlx_ptr, data->images.west.img);
		if (data->images.north.img)
			mlx_destroy_image(data->mlx_ptr, data->images.north.img);
		if (data->images.south.img)
			mlx_destroy_image(data->mlx_ptr, data->images.south.img);
		if (data->win)
			mlx_destroy_window(data->mlx_ptr, data->win);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	//free_mlx_data(&data->mlx);
	//free_game_data(&data->game);
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
