/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:21:48 by trobin            #+#    #+#             */
/*   Updated: 2021/09/23 13:24:41 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*		OLD
int		is_wall_EW(double intersecx, double intersecy, double rayx, char **map)
{
	if (rayx < 0)
	{
		if (map[(int)intersecy][(int)intersecx - 1] == '1')
			return 1;
		return 0;
	}
	if (rayx > 0)
	{
		if (map[(int)intersecy][(int)intersecx] == '1')
			return 1;
		return 0;
	}
	return 0;
}

int		is_wall_NS(double intersecx, double intersecy, double rayy, char **map)
{
	if (rayy < 0)
	{
		if (map[(int)intersecy - 1][(int)intersecx] == '1')
			return 1;
		return 0;
	}
	if (rayy > 0)
	{
		if (map[(int)intersecy][(int)intersecx] == '1')
			return 1;
		return 0;
	}
	return 0;
}

double	get_dist_EW(double posx, double posy, double rayx, double rayy, char **map,
					double angle, t_img *img)
{
	double stepx;

	if (rayx > 1e-10)
		stepx = 1.0;
	else if (rayx < -1e-10)
		stepx = -1.0;
	else
		return 9999.9;

	double deltax = (trunc(posx) + CUB_LENGTH - posx) * stepx;
	double deltay = rayy / rayx * deltax;
//	printf("first deltax = %f\n", deltax);
//	printf("first deltay = %f\n", deltay);

	double intersecx = posx + deltax;
	double intersecy = posy + deltay;
//	printf("first intersec E/W: (%f;%f)\n", intersecx, intersecy);

	double dist_EW = sqrt((deltax * deltax) + (deltay * deltay));
//	printf("distance to first intersec E/W: %f\n", dist_EW);

	double const_deltax = CUB_LENGTH * stepx;
	double const_deltay = rayy / rayx * const_deltax;
	double const_dist_EW = sqrt((const_deltax * const_deltax) + (const_deltay * const_deltay));
//	printf("Pour trouver un nouveau mur E/W il faut:\n");
//	printf("- Avancer sur l'axe `x` de %f\n", const_deltax);
//	printf("- Avancer sur l'axe `y` de %f\n", const_deltay);
//	printf("(i.e. prolonger le rayon d'une longueur de %f)\n", const_dist_EW);

	while (!is_wall_EW(intersecx, intersecy, rayx, map))
	{
	//	ray_EW_to_image(rayx, intersecx, intersecy, const_deltay, img);
	//	printf("EW intersec = %.10f ; %.10f\n", intersecx, intersecy);
		intersecx += const_deltax;
		intersecy += const_deltay;
		dist_EW += const_dist_EW;
	}
	printf("EW intersec = %.10f ; %.10f\n", intersecx, intersecy);
	if (rayx > 0)
		printf("Mur E trouve en map[%d][%d]\n", (int)intersecy, (int)intersecx);
	else
		printf("Mur W trouve en map[%d][%d]\n", (int)intersecy - 1, (int)intersecx);
 	// Fisheye correction
	return (dist_EW * cos(fabs(FOV_RAD / 2.0 - angle)));
}

double	get_dist_NS(double posx, double posy, double rayx, double rayy, char **map,
					double angle, t_img *img)
{
	double stepy;

	if (rayy > 1e-10)
		stepy = 1.0;
	else if (rayy < -1e-10)
		stepy = -1.0;
	else
		return 9999.9;

	double deltay = (trunc(posy) + CUB_LENGTH - posy) * stepy;
	double deltax = rayx / rayy * deltay;
//	printf("first deltax = %f\n", deltax);
//	printf("first deltay = %f\n", deltay);

	double intersecx = posx + deltax;
	double intersecy = posy + deltay;
//	printf("first intersec N/S: (%f;%f)\n", intersecx, intersecy);

	double dist_NS = sqrt((deltax * deltax) + (deltay * deltay));
//	printf("distance to first intersec N/S: %f\n", dist_NS);

	double const_deltay = CUB_LENGTH * stepy;
	double const_deltax = rayx / rayy * const_deltay;
	double const_dist_NS = sqrt((const_deltax * const_deltax) + (const_deltay * const_deltay));
//	printf("Pour trouver un nouveau mur N/S il faut:\n");
//	printf("- Avancer sur l'axe `x` de %f\n", const_deltax);
//	printf("- Avancer sur l'axe `y` de %f\n", const_deltay);
//	printf("(i.e. prolonger le rayon d'une longueur de %f)\n", const_dist_NS);

	while (!is_wall_NS(intersecx, intersecy, rayy, map))
	{
		//ray_NS_to_image(rayy, intersecx, intersecy, const_deltax, img);
		//printf("NS intersec = %.10f ; %.10f\n", intersecx, intersecy);
		intersecx += const_deltax;
		intersecy += const_deltay;
		dist_NS += const_dist_NS;
	}
	printf("NS intersec = %.10f ; %.10f\n", intersecx, intersecy);
	if (rayy > 0)
		printf("Mur S trouve en map[%d][%d]\n", (int)intersecy, (int)intersecx);
	else
		printf("Mur N trouve en map[%d][%d]\n", (int)intersecy - 1, (int)intersecx);
 	// Fisheye correction
	return (dist_NS * cos(fabs(FOV_RAD / 2.0 - angle)));
}

//void	column_to_image(t_img *img, t_color *color, double dist)
//{
//	//int h = 1;
//
//	// definir un intervalle bas-du-mur/haut-du-mur
//
//	// dist = 0 --> height = resolution.y;
//	// dist = 1 --> height = resolution.y * 0.9
//	;
//}

void	cast(double posx, double posy, double rayx, double rayy, t_img *img, char **map,
				double angle)
{
	double dist_NS = get_dist_NS(posx, posy, rayx, rayy, map, angle, img);
	double dist_EW = get_dist_EW(posx, posy, rayx, rayy, map, angle, img);
	//ray_to_image(posx, posy, rayx, rayy, map, angle, img);
	//t_color color;

	printf("dist_NS = %.10f\n", dist_NS);
	printf("dist_EW = %.10f\n", dist_EW);
	if (dist_NS < dist_EW)
	{
		if (rayy > 0)
		{
		//	printf("Mur S plus pres\n");
			// SOUTH_COLOR is RED
		//	color.red = 255;
		//	color.green = 0;
		//	color.blue = 0;
		}
		else
		{
		//	printf("Mur N plus pres\n");
			// NORTH_COLOR is BLUE;
		//	color.red = 0;
		//	color.green = 0;
		//	color.blue = 255;
		}
		return ;
	//	return (column_to_image(img, &color, dist_NS));
	}
	else
	{
		if (rayx > 0)
		{
		//	printf("Mur E plus pres\n");
			// EST_COLOR is GREEN
		//	color.red = 0;
		//	color.green = 255;
		//	color.blue = 0;
		}
		else
		{
		//	printf("Mur W plus pres\n");
			// WEST_COLOR is WHITE
		//	color.red = 255;
		//	color.green = 255;
		//	color.blue = 255;
		}
		return ;
		//return (column_to_image(img, &color, dist_EW));
	}
}

void	raycasting(t_data *data)
{

//	double rayx = data->game.pos->x + data->game.dir->x - data->game.plane->x;
//	double rayy = data->game.pos->y + data->game.dir->y - data->game.plane->y;
//
//	double delta_ray = FOV_RAD / data->game.resolution->x;
//	double delta_rayx = 2 * data->game.plane->x / data->game.resolution->x;
//	double delta_rayy = 2 * data->game.plane->y / data->game.resolution->x;
//	double angle_ray = FOV_RAD / 2 * (-1);

	// cast all rays
//	int i = 0;
//	while (i < data->game.resolution->x)
//	{
//		cast(data->game.pos->x, data->game.pos->y, rayx, rayy,
//			&data->mlx.img, data->game.map, abs(angle_ray));
//		rayx += delta_rayx;
//		rayy += delta_rayy;
//		angle_ray += delta_ray;
//		++i;
//	}

	printf("========== Left ray ==========\n");
	cast(
		data->game.pos->x, data->game.pos->y,
		data->game.dir->x - data->game.plane->x,
		data->game.dir->y - data->game.plane->y,
		&data->mlx.img, data->game.map, FOV_RAD / 2);
	printf("========== Mid ray ============\n");
	cast(
		data->game.pos->x, data->game.pos->y,
		data->game.dir->x, data->game.dir->y,
		&data->mlx.img, data->game.map, 0);
	printf("========== Right ray ==========\n");
	cast(
		data->game.pos->x, data->game.pos->y,
		data->game.dir->x + data->game.plane->x,
		data->game.dir->y + data->game.plane->y,
		&data->mlx.img, data->game.map, FOV_RAD / 2);
}
*/

/*		NEW
double	get_dist_S(t_vector pos, t_vector map, double angle, double stepx, t_data *data)
{
//	if (angle == 0)
//		return 9999;

	printf("\n====get_dist_S====\n");
	printf("angle: %f\n", angle);
	printf("cos(angle): %f\n", cos(angle));

	double first_deltay = SQUARE_LENGTH * (map.y + 1) - pos.y;
	double first_dist = first_deltay / cos(angle);
	double first_deltax = first_dist * sin(angle) * stepx;

	printf("first_deltay: %f\n", first_deltay);
	printf("first_dist: %f\n", first_dist);
	printf("first_deltax: %f\n", first_deltax);

	// remplacer const_delta.y par SQUARE_LENGTH --> 25 lignes !!!
	double const_deltay = SQUARE_LENGTH;
	double const_dist = const_deltay / cos(angle);
	double const_deltax = const_dist * sin(angle) * stepx;

	pos.x += first_deltax;
	pos.y += first_deltay;

	map.x = floor(pos.x / SQUARE_LENGTH);
	map.y = floor(pos.y / SQUARE_LENGTH);

	printf("map.x = %d\n", (int)map.x);
	printf("map.y = %d\n", (int)map.y);

	double dist = first_dist;
	while (data->game.map[(int)map.y][(int)map.x] == '0')
	//	data->game.map[(int)map.y - 1][(int)map.x] == '0'
	{
		pos.x += const_deltax;
		pos.y += const_deltay;
		dist += const_dist;
		map.x = floor(pos.x / SQUARE_LENGTH);
		map.y = floor(pos.y / SQUARE_LENGTH);
	}
	//printf("\nLAST INTERSEC POS | [%f;%f]\n", pos.x, pos.y);
	//printf("THERE IS SOUTH WALL IN [%d][%d]\n", (int)map.x, (int)map.y);
	printf("dist sud = %f\n", dist * cos(angle));
	printf("====================\n");
	return (dist * cos(angle));
}

double	get_dist_N(t_vector pos, t_vector map, double angle, double stepx, t_data *data)
{
//	if (angle == 0)
//		return 9999;
	
	// avoid div by zero : cos(pi/2) = 0
	if (angle == M_PI / 2)
		angle = 0;

	double first_deltay = pos.y - SQUARE_LENGTH * map.y;
	double first_dist = first_deltay / cos(angle);
	double first_deltax = first_dist * sin(angle) * stepx;

//	printf("first_deltax = %f\n", first_deltax);
//	printf("first_deltay = %f\n", first_deltay);

	// remplacer const_delta.y par SQUARE_LENGTH --> 25 lignes !!!
	double const_deltay = SQUARE_LENGTH;
	double const_dist = const_deltay / cos(angle);
	double const_deltax = const_dist * sin(angle) * stepx;

	pos.x += first_deltax;
	pos.y -= first_deltay;

	map.x = floor(pos.x / SQUARE_LENGTH);
	map.y = floor(pos.y / SQUARE_LENGTH - 1);

	double dist = first_dist;
	while (data->game.map[(int)map.y][(int)map.x] == '0')
	//	data->game.map[(int)map.y + 1][(int)map.x] == '0'
	{
		pos.x += const_deltax;
		pos.y -= const_deltay;
		dist += const_dist;
		map.x = floor(pos.x / SQUARE_LENGTH);
		map.y = floor(pos.y / SQUARE_LENGTH - 1);
	}
	//printf("\nLAST INTERSEC POS | [%f;%f]\n", pos.x, pos.y);
	//printf("THERE IS NORTH WALL IN [%d][%d]\n", (int)map.x, (int)map.y);
	return (dist * cos(angle));
}

double	get_dist_W(t_vector pos, t_vector map, double angle, double stepy, t_data *data)
{
//	if (angle == 0)
//		return 9999;

	printf("\n====get_dist_W====\n");
	printf("angle: %f\n", angle);
	printf("cos(angle): %f\n", cos(angle));

	double first_deltax = (pos.x - map.x * SQUARE_LENGTH);
	double first_dist = first_deltax / cos(angle);
	double first_deltay = first_dist * sin(angle) * stepy;

	printf("first_deltay: %f\n", first_deltay);
	printf("first_dist: %f\n", first_dist);
	printf("first_deltax: %f\n", first_deltax);

	// remplacer const_delta.x par SQUARE_LENGTH --> 25 lignes !!!
	double const_deltax = SQUARE_LENGTH;
	double const_dist = const_deltax / cos(angle);
	double const_deltay = const_dist * sin(angle) * stepy;

	pos.x -= first_deltax;
	pos.y += first_deltay;

	map.x = floor(pos.x / SQUARE_LENGTH - 1);
	map.y = floor(pos.y / SQUARE_LENGTH);

	printf("map.x = %d\n", (int)map.x);
	printf("map.y = %d\n", (int)map.y);

	double dist = first_dist;
	while (data->game.map[(int)map.y][(int)map.x] == '0')
	//	data->game.map[(int)map.y][(int)map.x + 1] == '0'
	{
		pos.x -= const_deltax;
		pos.y += const_deltay;
		dist += const_dist;
		map.x = floor(pos.x / SQUARE_LENGTH - 1);
		map.y = floor(pos.y / SQUARE_LENGTH);
	}
	//printf("\nLAST INTERSEC POS | [%f;%f]\n", pos.x, pos.y);
	//printf("THERE IS WEST WALL IN [%d][%d]\n", (int)map.x, (int)map.y);
	return (dist * cos(angle));
}

double	get_dist_E(t_vector pos, t_vector map, double angle, double stepy, t_data *data)
{
	//if (angle ==  M_PI / 2)
	//	return 9999;

	double first_deltax = (map.x + 1) * SQUARE_LENGTH - pos.x;
	double first_dist = first_deltax / cos(angle);
	double first_deltay = first_dist * sin(angle) * stepy;

	// remplacer const_delta.x par SQUARE_LENGTH --> 25 lignes !!!
	double const_deltax = SQUARE_LENGTH;
	double const_dist = const_deltax / cos(angle);
	double const_deltay = const_dist * sin(angle) * stepy;

	pos.x += first_deltax;
	pos.y += first_deltay;

	map.x = floor(pos.x / SQUARE_LENGTH);
	map.y = floor(pos.y / SQUARE_LENGTH);

	double dist = first_dist;
	while (data->game.map[(int)map.y][(int)map.x] == '0')
	//	&& data->game.map[(int)map.y][(int)map.x - 1] == '0'
	{
//		printf("\nINTERSEC POS | [%f;%f]\n", pos.x, pos.y);
//		printf("NO WALL FOR [%d][%d]\n", (int)map.x, (int)map.y);
		pos.x += const_deltax;
		pos.y += const_deltay;
		dist += const_dist;
		map.x = floor(pos.x / SQUARE_LENGTH);
		map.y = floor(pos.y / SQUARE_LENGTH);
	}
	//printf("\nLAST INTERSEC POS | [%f;%f]\n", pos.x, pos.y);
	//printf("THERE IS EST WALL IN [%d][%d]\n", (int)map.x, (int)map.y);
	return (dist * cos(angle));
}

void	column_to_image(unsigned int color, double dist, t_img *img, t_vector resolution, int column)
{
	double wall_height = SQUARE_LENGTH / dist * resolution.y;
	// on peut ajouter un facteur k, tel que : dist * k
	// si k = 0.5, le mur va retrecir deux fois moins vite a mesure qu'on recule

	int mid_screen = (int)(resolution.y / 2);

	// draw wall
	int i = 0;
	while (i < wall_height / 2)
	{
		pixel_to_image(img, mid_screen - i, column, color);
		pixel_to_image(img, mid_screen + i, column, color);
		i++;
	}

	// draw sky and floor
	while (i < resolution.y / 2)
	{
		pixel_to_image(img, mid_screen - i, column, SKY_COLOR);
		pixel_to_image(img, mid_screen + i, column, FLOOR_COLOR);
		i++;
	}
}

void	cast(t_vector pos, t_vector map, double ray, t_img *img, t_vector *resolution, int column, t_data *data)
{
	double dist_EW;
	double dist_NS;
	double stepx;
	double stepy;
	unsigned int ns_color;
	unsigned int ew_color;
	double ns_angle;
	double ew_angle;

	if (0 <= ray && ray < M_PI / 2)
	{
		ns_angle = M_PI / 2 - ray;
		ew_angle = ray;
		stepx = 1;
		stepy = 1;
		ew_color = E_COLOR;
		ns_color = S_COLOR;
		dist_EW = get_dist_E(pos, map, ew_angle, stepy, data);
		if (ray == 0)
			dist_NS = 9999;
		else
			dist_NS = get_dist_S(pos, map, ns_angle, stepx, data);
	}
	else if (M_PI / 2 <= ray && ray < M_PI)
	{
		ns_angle = ray - M_PI / 2;
		ew_angle = M_PI - ray;
		stepx = -1;
		stepy = 1;
		ew_color = W_COLOR;
		ns_color = S_COLOR;
		dist_NS = get_dist_S(pos, map, ns_angle, stepx, data);
		if (ray == M_PI / 2)
			dist_EW = 9999;
		else
			dist_EW = get_dist_W(pos, map, ew_angle, stepy, data);
	}
	else if (M_PI <= ray && ray < 3 * M_PI / 2)
	{
		ew_angle = ray - M_PI;
		ns_angle = 3 * M_PI / 2 - ray;
		stepx = -1;
		stepy = -1;
		ew_color = W_COLOR;
		ns_color = N_COLOR;
		dist_EW = get_dist_W(pos, map, ew_angle, stepy, data);
		if (ray == M_PI)
			dist_NS = 9999;
		else
			dist_NS = get_dist_N(pos, map, ns_angle, stepx, data);
	}
	else if (3 * M_PI / 2 <= ray && ray < 2 * M_PI)
	{
		ew_angle = 2 * M_PI - ray;
		ns_angle = ray = 3 * M_PI / 2;
		stepx = 1;
		stepy = -1;
		ew_color = E_COLOR;
		ns_color = N_COLOR;
		dist_NS = get_dist_N(pos, map, ns_angle, stepx, data);
		if (ray == 3 * M_PI / 2)
			dist_EW = 9999;
		else
			dist_EW = get_dist_E(pos, map, ew_angle, stepy, data);
	}
	if (dist_EW < dist_NS)
		printf("dist = %f\n", dist_EW);
		//return (column_to_image(ew_color, dist_EW, img, *resolution, column));
	else
		printf("dist = %f\n", dist_NS);
		//return (column_to_image(ns_color, dist_NS, img, *resolution, column));
}

void	raycasting(t_data *data)
{
	// init ces variables dans `init_cub3d()` ?
	// init en variables de preprocesseur ?
	double ray = data->game.dir - FOV_RAD / 2;
	double max = data->game.dir + FOV_RAD / 2;
	double rot = FOV_RAD / data->game.resolution->x;

	t_vector *pos = data->game.pos;

	t_vector map;
	map.x = floor(pos->x / SQUARE_LENGTH);
	map.y = floor(pos->y / SQUARE_LENGTH);

	//int column = 0;
	//while (ray < max)
	//{
	//	printf("\tray n.%d: %f rad -- ", column, ray);
	//	printf("pos [%d, %d]\n", (int)pos->x, (int)pos->y);
	//	cast(*pos, map, ray, &data->mlx.img, data->game.resolution, column, data);
	//	ray += rot;
	//	column++;
	//}
//	cast(*pos, map, data->game.dir, &data->mlx.img, data->game.resolution, 0, data);
	printf("RAY   | %lf rad --> we cast this!\n", fabs(FOV_RAD / 2 - data->game.dir));
	cast(*pos, map, data->game.dir - FOV_RAD / 2 - M_PI / 2, &data->mlx.img,
		data->game.resolution, 0, data);
//	cast(*pos, map, fabs(3 * FOV_RAD / 2 - data->game.dir), &data->mlx.img,
//		data->game.resolution, 0, data);
}
*/

/*
//		NEW 2.0
//		T0D0 : 
//			- add map as param and group map and pos into t_player
//			- add stepy and stepx when missing 
//			- operations on vectors ('+', '=', '/', etc.)
double	get_dist_E(t_vector pos, double angle, double stepy, t_data *data)
{
	double first_deltax = floor(pos.x / SQUARE_LENGTH) * SQUARE_LENGTH - pos.x;
	double first_dist = first_deltax / cos(angle);
	double first_deltay = first_dist * sin(angle) * stepy;

	double const_deltax = SQUARE_LENGTH;
	double const_dist = const_deltax / cos(angle);
	double const_deltay = const_dist * sin(angle) * stepy;

	pos.x += first_deltax;
	pos.y += first_deltay;

	int mapx = (int)(pos.x / SQUARE_LENGTH);
	int mapy = (int)(pos.y / SQUARE_LENGTH);

	double dist = first_dist;
	while (data->game.map[mapy][mapx] == '0')
	{
		pos.x += const_deltax;
		pos.y += const_deltay;
		dist += const_dist;
		mapx = (int)(pos.x / SQUARE_LENGTH);
		mapy = (int)(pos.y / SQUARE_LENGTH);
	}
	return (dist * cos(angle));
}

double	get_dist_W(t_vector pos, double angle, double stepy, t_data *data)
{
	double first_deltax = pos.x - floor(pos.x / SQUARE_LENGTH) * SQUARE_LENGTH;// * stepx ?
	double first_dist = first_deltax / cos(angle);
	double first_deltay = first_dist * sin(angle) * stepy;

	printf("==== W ====\n");
	printf("ew_angle = %f\n", angle);
	printf("first_deltax = %f\n", first_deltax);
	printf("first_deltay = %f\n", first_deltay);
	printf("first_dist = %f\n", first_dist);

	double const_deltax = SQUARE_LENGTH; // * stepx ?
	double const_dist = const_deltax / cos(angle);
	double const_deltay = const_dist * sin(angle) * stepy;

	pos.x -= first_deltax;
	pos.y += first_deltay;

	int mapx = (int)(pos.x / SQUARE_LENGTH);
	int mapy = (int)(pos.y / SQUARE_LENGTH);

	double dist = first_dist;
	while (data->game.map[mapy][mapx - 1] == '0')
	{
		pos.x -= const_deltax;
		pos.y += const_deltay;
		dist += const_dist;
		mapx = (int)(pos.x / SQUARE_LENGTH);
		mapy = (int)(pos.y / SQUARE_LENGTH);
	}
	printf("===========\n");
	return (dist * cos(angle));
}

double	get_dist_S(t_vector pos, double angle, double stepx, t_data *data)
{
	double first_deltay = SQUARE_LENGTH * (floor)(pos.y / SQUARE_LENGTH + 1) - pos.y;
	double first_dist = first_deltay / cos(angle);
	double first_deltax = first_dist * sin(angle) * stepx;

	double const_deltay = SQUARE_LENGTH;
	double const_dist = const_deltay / cos(angle);
	double const_deltax = const_dist * sin(angle) * stepx;

	pos.x += first_deltax;
	pos.y += first_deltay;

	int mapx = (int)(pos.x / SQUARE_LENGTH);
	int mapy = (int)(pos.y / SQUARE_LENGTH);

	double dist = first_dist;
	while (data->game.map[mapy][mapx] == '0')
	{
		pos.x += const_deltax;
		pos.y += const_deltay;
		dist += const_dist;
		mapx = (int)(pos.x / SQUARE_LENGTH);
		mapy = (int)(pos.y / SQUARE_LENGTH);
	}
	return (dist * cos(angle));
}

double	get_dist_N(t_vector pos, double angle, double stepx, t_data *data)
{
	double first_deltay = pos.y - floor(pos.y / SQUARE_LENGTH) * SQUARE_LENGTH; // * stepy ?
	double first_dist = first_deltay / cos(angle);
	double first_deltax = first_dist * sin(angle) * stepx;

	printf("==== N ====\n");
	printf("ns_angle = %f\n", angle);
	printf("first_deltay = %f\n", first_deltay);
	printf("first_dist = %f\n", first_dist);
	printf("first_deltax = %f\n", first_deltax);

	double const_deltay = SQUARE_LENGTH;// * stepy ? (* -1)
	double const_dist = const_deltay / cos(angle);
	double const_deltax = const_dist * sin(angle) * stepx;

	// OLD : jump to first intersec (can be outside of map !!!)
//	pos.x += first_deltax;
//	pos.y -= first_deltay;

//	int mapx = (int)(pos.x / SQUARE_LENGTH);
//	int mapy = (int)(pos.y / SQUARE_LENGTH);

//	double dist = first_dist;
//	while (data->game.map[mapy - 1][mapx] == '0')
//	{
//		pos.x += const_deltax;
//		pos.y -= const_deltay;
//		dist += const_dist;
//		mapx = (int)(pos.x / SQUARE_LENGTH);
//		mapy = (int)(pos.y / SQUARE_LENGTH);
//	}
	
	// NEW : go cell by cell, until intersec
	pos.x += first_deltax;
	pos.y -= first_deltay;

	int mapx = (int)(pos.x / SQUARE_LENGTH);
	int mapy = (int)(pos.y / SQUARE_LENGTH) - 1;

	double dist = first_dist;
	while (data->game.map[mapy][mapx] != '1')
	{
		pos.x += const_deltax;
		pos.y -= const_deltay;
		dist += const_dist;
		mapx = (int)(pos.x / SQUARE_LENGTH);
		mapy = (int)(pos.y / SQUARE_LENGTH);
	}
	printf("===========\n");
	return (dist * cos(angle));
}

void	column_to_image(unsigned int color, double dist, t_img *img, t_vector resolution, int column)
{
	double wall_height = SQUARE_LENGTH / dist * resolution.y;
	// on peut ajouter un facteur k, tel que : dist * k
	// si k = 0.5, le mur va retrecir deux fois moins vite a mesure qu'on recule

	int mid_screen = (int)(resolution.y / 2);

	// draw wall
	int i = 0;
	while (i < wall_height / 2)
	{
		pixel_to_image(img, mid_screen - i, column, color);
		pixel_to_image(img, mid_screen + i, column, color);
		i++;
	}

	// draw sky and floor
	while (i < resolution.y / 2)
	{
		pixel_to_image(img, mid_screen - i, column, SKY_COLOR);
		pixel_to_image(img, mid_screen + i, column, FLOOR_COLOR);
		i++;
	}
}

void	cast(t_vector pos, double ray, t_img *img, t_vector *resolution,
			int column, t_data *data)
{
	double dist_EW;
	double dist_NS;
	double stepx;
	double stepy;
	unsigned int ns_color;
	unsigned int ew_color;
	double ns_angle;
	double ew_angle;

	if (0 <= ray && ray < M_PI / 2)
	{
		ns_angle = M_PI / 2 - ray;
		ew_angle = ray;
		stepx = 1;
		stepy = 1;
		ew_color = E_COLOR;
		ns_color = S_COLOR;
		dist_EW = get_dist_E(pos, ew_angle, stepy, data);
		if (ray == 0)
			dist_NS = 9999;
		else
			dist_NS = get_dist_S(pos, ns_angle, stepx, data);
	}
	else if (M_PI / 2 <= ray && ray < M_PI)
	{
		ns_angle = ray - M_PI / 2;
		ew_angle = M_PI - ray;
		stepx = -1;
		stepy = 1;
		ew_color = W_COLOR;
		ns_color = S_COLOR;
		dist_NS = get_dist_S(pos, ns_angle, stepx, data);
		if (ray == M_PI / 2)
			dist_EW = 9999;
		else
			dist_EW = get_dist_W(pos, ew_angle, stepy, data);
	}
	else if (M_PI <= ray && ray < 3 * M_PI / 2)
	{
		printf("__yo\n");
		ew_angle = ray - M_PI;
		ns_angle = (3 * M_PI / 2) - ray;
		stepx = -1;
		stepy = -1;
		ew_color = W_COLOR;
		ns_color = N_COLOR;
		dist_EW = get_dist_W(pos, ew_angle, stepy, data);
		printf("__ya\n");
		if (ray == M_PI)
			dist_NS = 9999;
		else
			dist_NS = get_dist_N(pos, ns_angle, stepx, data);

	}
	else if (3 * M_PI / 2 <= ray && ray < 2 * M_PI)
	{
		ew_angle = 2 * M_PI - ray;
		ns_angle = ray - 3 * M_PI / 2;
		stepx = 1;
		stepy = -1;
		ew_color = E_COLOR;
		ns_color = N_COLOR;
		dist_NS = get_dist_N(pos, ns_angle, stepx, data);
		if (ray == 3 * M_PI / 2)
			dist_EW = 9999;
		else
			dist_EW = get_dist_E(pos, ew_angle, stepy, data);
	}
	printf("dist_EW = %f\n", dist_EW);
	printf("dist_NS = %f\n", dist_NS);
	if (dist_EW < dist_NS)
		printf("dist = %f\n", dist_EW);
		//return (column_to_image(ew_color, dist_EW, img, *resolution, column));
	else
		printf("dist = %f\n", dist_NS);
		//return (column_to_image(ns_color, dist_NS, img, *resolution, column));
}

void	raycasting(t_data *data)
{
	// init ces variables dans `init_cub3d()` ? (ou en preprocesseur)
	double ray = data->game.dir - FOV_RAD / 2;
	double max = data->game.dir + FOV_RAD / 2;
	double rot = FOV_RAD / data->game.resolution->x;

	t_vector *pos = data->game.pos;

	//int column = 0;
	//while (ray < max)
	//{
	//	printf("\tray n.%d: %f rad -- ", column, ray);
	//	printf("pos [%d, %d]\n", (int)pos->x, (int)pos->y);
	//	cast(*pos, ray, &data->mlx.img, data->game.resolution, column, data);
	//	ray += rot;
	//	column++;
	//}

	printf("RAY   | %lf rad\n", data->game.dir + rot);
	cast(*pos, data->game.dir + rot, &data->mlx.img, data->game.resolution, 0, data);

//	cast(*pos, fabs(3 * FOV_RAD / 2 - data->game.dir), &data->mlx.img,
//		data->game.resolution, 0, data);
}
*/
