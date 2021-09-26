/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_pixel_to_image.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:03:22 by trobin            #+#    #+#             */
/*   Updated: 2021/04/16 12:16:01 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//void	square_pixel_to_image(t_img *img, int x, int y, int color)
//{
//	pixel_to_image(img, y, x, color);
//	pixel_to_image(img, y, x + 1, color);
//	pixel_to_image(img, y, x + 2, color);
//	pixel_to_image(img, y + 1, x, color);
//	pixel_to_image(img, y + 2, x, color);
//	pixel_to_image(img, y + 1, x + 1, color);
//	pixel_to_image(img, y + 2, x + 1, color);
//	pixel_to_image(img, y + 2, x + 2, color);
//	pixel_to_image(img, y + 1, x + 2, color);
//}


void	square_pixel_to_image(t_img *img, int x, int y, int color)
{
	int tmp;
	int max;

	// see src/gfx/map_to_image.c
	// each cell is drawn on 8x8 pixels
	max = y + SQUARE_LENGTH;
	while (y < max)
	{
		tmp = 0;
		while (tmp < SQUARE_LENGTH)
		{
			pixel_to_image(img, y, x + tmp, color);
			tmp++;
		}
		y++;
	}
}
