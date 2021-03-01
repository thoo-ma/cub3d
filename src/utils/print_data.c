/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 12:52:51 by trobin            #+#    #+#             */
/*   Updated: 2021/09/23 18:23:14 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_player_data(t_player *player)
{
	printf("MAP   | [%d;%d]\n", player->map.x, player->map.y);
	printf("POS   | [%f;%f]\n", player->pos.x, player->pos.y);
	printf("DIR   | %f\n", player->dir);
	printf("PLANE | %f\n", player->plane);
}

void	print_image_data(t_img *img, const char *s)
{
	if (img)
	{
		printf("== %s ==\n", s);
		printf("%s.img   : %p\n", s, img->img);
		printf("%s.addr  : %p\n", s, img->addr);
		printf("%s.bpp   : %d\n", s, img->bpp);
		printf("%s.ll    : %d\n", s, img->ll);
		printf("%s.endian: %d\n", s, img->endian);
	}
}

void	print_color_data(t_color *color, const char *s)
{
	if (color)
	{
		printf("== %s ==\n", s);
		printf("%s.r: %d\n", s, color->r);
		printf("%s.g: %d\n", s, color->g);
		printf("%s.b: %d\n", s, color->b);
	}
}

void	print_data(t_data *data)
{
	// colors
	if (data->colors.floor.parsed)
		print_color_data(&data->colors.floor, "floor");
	if (data->colors.ceiling.parsed)
		print_color_data(&data->colors.ceiling, "ceiling");

	// images
	if (data->images.est.img)
		print_image_data(&data->images.est, "est");
	if (data->images.west.img)
		print_image_data(&data->images.west, "west");
	if (data->images.north.img)
		print_image_data(&data->images.north, "north");
	if (data->images.south.img)
		print_image_data(&data->images.south, "south");

	// map
	if (data->map)
		print_2d_array(data->map);

	// player
//	print_player_data(data);
//	if (data->pos)
//		printf("pos vector:\t(%f; %f)\n", data->pos->x, data->pos->y);
//	if (data->dir)
//		printf("dir vector:\t(%f; %f)\n", data->dir->x, data->dir->y);
//	if (data->plane)
//		printf("plane vector:\t(%f; %f)\n", data->plane->x, data->plane->y);
}
