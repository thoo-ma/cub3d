/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 06:57:57 by trobin            #+#    #+#             */
/*   Updated: 2021/09/23 14:00:15 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_mlx_instance(t_data *data)
{
	data->mlx_ptr = 0;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit_cub3d(data, MLX_INIT);
}

void	get_mlx_window(t_data *data)
{
	data->win = 0;
	data->win = mlx_new_window(data->mlx_ptr, WIN_X, WIN_Y, "cub3D");
	if (!data->win)
		exit_cub3d(data, MLX_WINDOW);
}

void	init_my_strerror(const char **my_strerror)
{
	my_strerror[MAP_MALLOC] = "map couldn't be malloced";
	my_strerror[MAP_ENOENT] = "map : no such file or directory";
	my_strerror[MAP_EACCES] = "map : permission denied";
	my_strerror[MAP_EISDIR] = "map is a directory";
	my_strerror[MAP_OPEN] = "cannot open map";
	my_strerror[MAP_READ] = "map read() failed";
	my_strerror[MAP_LINE_FORMAT] = "line from .cub not well formatted";
	my_strerror[MAP_EXTENSION] = "map is not a .cub file";
	my_strerror[MAP_NOT_CLOSE] = "map is not closed by walls";
	my_strerror[MAP_FT_STRNCAT] = "get_map(): ft_strncat() failed";
	my_strerror[MAP_FT_SPLIT] = "get_map() : ft_split() failed";
	my_strerror[MAP_DUPLICATE] = "map splited by newline(s)";
	my_strerror[MAP_UNDEFINED] = "map contains undefined cells";
	my_strerror[MAP_NO_CARDINAL] = "map contains no player";
	my_strerror[MAP_MULT_CARDINALS] = "map contains multiple players";
	my_strerror[MLX_INIT] = "mlx_init() failed";
	my_strerror[MLX_WINDOW] = "mlx_new_window() failed";
	my_strerror[XPM_FORMAT] = "texture line not well formatted";
	my_strerror[XPM_DUPLICATE] = "xpm duplicate";
	my_strerror[XPM_UNAVAILABLE] = "unable to open xpm file";
	my_strerror[TEXTURE_MISSING] = "texture missing";
	my_strerror[IMG_ADDR] = "mlx_get_data_addr() failed";
	my_strerror[COLOR_FORMAT] = "color format incorrect";
	my_strerror[COLOR_MALLOC] = "get_color() : malloc() failed";
	my_strerror[COLOR_RANGE] = "color outside of range [0;255]";
	my_strerror[COLOR_MISSING] = "floor/ceiling color missing";
	my_strerror[COLOR_DUPLICATE] = "color duplicate";
	my_strerror[MAIN_ARG] = "cub3d need one and only argument";
}

void	init_images(t_images *images)
{
	images->est.img = 0;
	images->west.img = 0;
	images->north.img = 0;
	images->south.img = 0;
}

void	init_colors(t_colors *colors)
{
	colors->floor.parsed = 0;
	colors->ceiling.parsed = 0;
}

void	init_cub3d(t_data *data)
{
	data->map = 0;
	data->win = 0;
	get_mlx_instance(data);
	init_images(&data->images);
	init_colors(&data->colors);
	init_my_strerror(data->my_strerror);
}

/*
void	init_game_data(t_game_data *data)
{
	data->map = 0;
	data->est = 0;
	data->west = 0;
	data->north = 0;
	data->south = 0;
	data->sprite = 0;

	//init_color(&data->floor);
	//init_color(&data->ceiling);
	data->floor = 0;
	data->ceiling = 0;

	data->resolution = 0;
	//init_resolution(&data->resolution);

	data->pos = 0;
	//data->dir = 0;
	//data->plane = 0;
//	init_vector(&data->pos);
//	init_vector(&data->dir);
//	init_vector(&data->plane);

	// new ----> dir and plane are angles, not vectors
	data->dir = 0;
	data->plane = 0;
}

int		init_mlx_data(t_data *data)
{
	data->mlx.mlx = 0;
	data->mlx.win = 0;
	data->mlx.img.img = 0;
	data->mlx.img.addr = 0;
	
	// mlx init
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == 0)
		exit_cub3d(data, MLX_INIT);

	// mlx win
	data->mlx.win = mlx_new_window(data->mlx.mlx,
		(int)data->game.resolution->x, (int)data->game.resolution->y, "cub3d");
	if (data->mlx.win == 0)
		exit_cub3d(data, MLX_WINDOW);

	// mlx image
	data->mlx.img.img = mlx_new_image(data->mlx.mlx,
		(int)data->game.resolution->x, (int)data->game.resolution->y);
	if (data->mlx.img.img == 0)
	{
		free_mlx_data(&data->mlx);
		return (0);
	}
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img, &data->mlx.img.bpp, &data->mlx.img.ll, &data->mlx.img.endian);
	if (data->mlx.img.addr == 0)
	{
		free_mlx_data(&data->mlx);
		return (0);
	}
	printf("one pixel is coded into %d bits (i.e. %d bytes)\n",
		data->mlx.img.bpp, (data->mlx.img.bpp / 8));
	printf("one line  is coded into %d bits (i.e. %d bytes)\n",
		data->mlx.img.ll, (data->mlx.img.ll / 8));

	return (1);
}
*/
