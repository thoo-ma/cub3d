/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:01:10 by trobin            #+#    #+#             */
/*   Updated: 2021/10/11 18:47:47 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_to_image(t_image *image, int x, int y, int color)
{
	image->addr[y * WIN_SIZE + x] = color;
}

int	get_image_pixel_color(t_image *image, int col, int row)
{
	return ((int)image->addr[row * CUB_SIZE + col]);
}
