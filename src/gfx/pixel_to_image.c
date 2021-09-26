/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:01:10 by trobin            #+#    #+#             */
/*   Updated: 2021/03/31 11:01:26 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_to_image(t_img *img, int y, int x, int color)
{
	char *pixel;

	pixel = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(int *)pixel = color;
}
