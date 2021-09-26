/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:10:00 by trobin            #+#    #+#             */
/*   Updated: 2021/05/03 06:41:05 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_to_image(t_img *img, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				square_pixel_to_image(img, j * SQUARE_LENGTH, i * SQUARE_LENGTH, GREEN);
			else if (map[i][j] == '1')
				square_pixel_to_image(img, j * SQUARE_LENGTH, i * SQUARE_LENGTH, RED);
			else if (map[i][j] == ' ')
				square_pixel_to_image(img, j * SQUARE_LENGTH, i * SQUARE_LENGTH, WHITE);
			// OLD (pos takes a whole cub)
			//else
			//	square_pixel_to_image(img, j * SQUARE_LENGTH, i * SQUARE_LENGTH, BLUE);
			// NEW (pos takes only one pixel)
			else
			{
				square_pixel_to_image(img, j * SQUARE_LENGTH, i * SQUARE_LENGTH, GREEN);
				pixel_to_image(img,
					j * SQUARE_LENGTH + SQUARE_LENGTH / 2,
					i * SQUARE_LENGTH + SQUARE_LENGTH / 2, BLUE);
			}
			j++;
		}
		i++;
	}
	return (1);
}
