/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_to_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 06:13:14 by trobin            #+#    #+#             */
/*   Updated: 2021/09/23 17:38:17 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//		ERASE
void	erase_horizontal_ray_from_image(t_img *img, int x, int y)
{
	int z = SQUARE_LENGTH / 2;
	int i = 0;
	while (i < SQUARE_LENGTH)
	{
		pixel_to_image(img, y * SQUARE_LENGTH + z - 1, x * SQUARE_LENGTH + i, GREEN);
		pixel_to_image(img, y * SQUARE_LENGTH + z, x * SQUARE_LENGTH + i, GREEN);
		i++;
	}
}

void	erase_vertical_ray_from_image(t_img *img, int x, int y)
{
	int z = SQUARE_LENGTH / 2;
	int i = 0;
	while (i < SQUARE_LENGTH)
	{
		pixel_to_image(img, y * SQUARE_LENGTH + i, x * SQUARE_LENGTH + z - 1, GREEN);
		pixel_to_image(img, y * SQUARE_LENGTH + i, x * SQUARE_LENGTH + z, GREEN);
		i++;
	}
}

//void	erase_rays_from_image(
//	t_img *img, double *posx, double *posy, double *dirx, double *diry, char **map)
//{
//	int x = (int)*posx;
//	int y = (int)*posy;
//
//	if ((int)*dirx > 0)
//	{
//		while (!is_wall(map, ++x, y))
//			erase_horizontal_ray_from_image(img, x, y);
//	}
//	else if ((int)*dirx < 0)
//	{
//		while (!is_wall(map, --x, y))
//			erase_horizontal_ray_from_image(img, x, y);
//	}
//	else if ((int)*diry > 0)
//	{
//		while (!is_wall(map, x, ++y))
//			erase_vertical_ray_from_image(img, x, y);
//	}
//	else if ((int)*diry < 0)
//	{
//		while (!is_wall(map, x, --y))
//			erase_vertical_ray_from_image(img, x, y);
//	}
//}


//		WRITE
void	horizontal_ray_to_image(t_img *img, int x, int y)
{
	int z = SQUARE_LENGTH / 2;
	int i = 0;
	while (i < SQUARE_LENGTH)
	{
		pixel_to_image(img, y * SQUARE_LENGTH + z - 1, x * SQUARE_LENGTH + i, BLUE);
		pixel_to_image(img, y * SQUARE_LENGTH + z, x * SQUARE_LENGTH + i, BLUE);
		i++;
	}
}

void	vertical_ray_to_image(t_img *img, int x, int y)
{
	int z = SQUARE_LENGTH / 2;
	int i = 0;
	while (i < SQUARE_LENGTH)
	{
		pixel_to_image(img, y * SQUARE_LENGTH + i, x * SQUARE_LENGTH + z - 1, BLUE);
		pixel_to_image(img, y * SQUARE_LENGTH + i, x * SQUARE_LENGTH + z, BLUE);
		i++;
	}
}

void	rays_to_image(
	t_img *img, double *posx, double *posy, double *dirx, double *diry, char **map)
{
	int x = (int)*posx;
	int y = (int)*posy;

	if ((int)*dirx > 0)
	{
		while (!is_wall(map, ++x, y))
			horizontal_ray_to_image(img, x, y);
	}
	else if ((int)*dirx < 0)
	{
		while (!is_wall(map, --x, y))
			horizontal_ray_to_image(img, x, y);
	}
	else if ((int)*diry > 0)
	{
		while (!is_wall(map, x, ++y))
			vertical_ray_to_image(img, x, y);
	}
	else if ((int)*diry < 0)
	{
		while (!is_wall(map, x, --y))
			vertical_ray_to_image(img, x, y);
	}
}	


//		YOOOOOOOOOOOOOOOOOOOOOOOOO
void	ray_EW_to_image(double rayx, double intersecx, double intersecy,
						double deltay, t_img *img)
{
	double mapx = trunc(intersecx);
	double mapy = trunc(intersecy);

	double starty = arrondi(intersecy - mapy);
	double endy = arrondi(intersecy - mapy + deltay);
//	printf("starty = %f\n", starty);
//	printf("endy = %f\n", endy);

	double delta;
	if (starty > endy)
		delta = starty - endy;
	else
		delta = endy - starty;
//	printf("delta = %f\n", delta);

	int steps = (int)(delta * SQUARE_LENGTH / CUB_LENGTH);
//	printf("steps = %d\n", steps);

	int ray_len;
	if (steps == 0)
	{
		steps = 1;
		ray_len = SQUARE_LENGTH;
	}
	else
		ray_len = (int)(SQUARE_LENGTH / steps + 1);
//	printf("ray_len = %d\n", ray_len);

	int i = 0;
	int j = 0;
	while (i < SQUARE_LENGTH)
	{
		if ((SQUARE_LENGTH - i) % steps == 0)
			j = ray_len;
		else
			j = ray_len - 1;
		while (j)
		{
			pixel_to_image(img, (int)(mapy * SQUARE_LENGTH + starty * SQUARE_LENGTH),
			(int)(mapx * SQUARE_LENGTH + i), BLUE);
			j--;
			i++;
		}
		if (rayx > 0.0)
			starty += delta / SQUARE_LENGTH;
		else
			starty -= delta / SQUARE_LENGTH;
	}
}

void	ray_NS_to_image(double rayy, double intersecx, double intersecy,
						double deltax, t_img *img)
{
	double mapx = trunc(intersecx);
	double mapy = trunc(intersecy);

	double startx = arrondi(intersecx - mapx);
	double endx = arrondi(intersecx - mapx + deltax);
//	printf("startx = %f\n", startx);
//	printf("endx = %f\n", endx);

	double delta;
	if (startx > endx)
		delta = startx - endx;
	else
		delta = endx - startx;
//	printf("delta = %f\n", delta);

	int steps = (int)(delta * SQUARE_LENGTH / CUB_LENGTH);
//	printf("steps = %d\n", steps);

	int ray_len;
	if (steps == 0)
	{
		steps = 1;
		ray_len = SQUARE_LENGTH;
	}
	else
		ray_len = (int)(SQUARE_LENGTH / steps + 1);
//	printf("ray_len = %d\n", ray_len);

	int i = 0;
	int j = 0;
	while (i < SQUARE_LENGTH)
	{
		if ((SQUARE_LENGTH - i) % steps == 0)
			j = ray_len;
		else
			j = ray_len - 1;
		while (j)
		{
			pixel_to_image(img, (int)(mapy * SQUARE_LENGTH + i),
				(int)(mapx * SQUARE_LENGTH + startx * SQUARE_LENGTH), BLUE);
			j--;
			i++;
		}
		if (rayy > 0.0)
			startx += delta / SQUARE_LENGTH;
		else
			startx -= delta / SQUARE_LENGTH;
	}
}

//void	ray_to_image(double rayx, double rayy, double intersecx, double intersecy,
//					double deltax, double deltay, double dist, t_img *img)
//{
//	if (fabs(deltax) < fabs(deltay))
//		ray_NS_to_image(dist, );
//	else
//		ray_EW_to_image(dist);
//}
