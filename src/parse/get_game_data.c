/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_game_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:40:14 by trobin            #+#    #+#             */
/*   Updated: 2021/09/23 13:57:10 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_texture(t_data *data, t_img *img, char *line)
{
	int		x;
	int		y;

	if (img->img)
		exit_cub3d(data, XPM_DUPLICATE);

	if (*line != ' ')
		exit_cub3d(data, XPM_FORMAT);
	skip_spaces(&line);

	img->img = mlx_xpm_file_to_image(data->mlx_ptr, line, &x, &y);
	if (img->img == 0)
		exit_cub3d(data, XPM_UNAVAILABLE);

	img->addr = 0;
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
	if (img->addr == 0)
		exit_cub3d(data, IMG_ADDR);

}

void	check_color_digits(t_data *data, char **tmp, int i)
{
	if (ft_strcspn(tmp[i], BASE_DEC))
	{
		free_2d_array(tmp);
		exit_cub3d(data, COLOR_FORMAT);
	}
}

void	check_color_range(t_data *data, char **tmp, int i)
{
	int color;

	color = ft_atoi(tmp[i]);
	if (color < 0 || color > 255)
	{
		free_2d_array(tmp);
		exit_cub3d(data, COLOR_RANGE);
	}
}

void	get_color(t_data *data, t_color *color, char *line)
{
	char	**tmp;
	int		i;

	if (color->parsed)
		exit_cub3d(data, COLOR_DUPLICATE);
	skip_spaces(&line);
	tmp = 0;
	tmp = ft_split(line, ',');
	if (!tmp)
		exit_cub3d(data, COLOR_MALLOC);
	if (length_2d_array(tmp) != 3)
		exit_cub3d(data, COLOR_FORMAT);
	i = 0;
	while (i < 3)
	{
		check_color_digits(data, tmp, i);
		check_color_range(data, tmp, i);
		i++;
	}
	color->r = (unsigned char)ft_atoi(tmp[0]);
	color->g = (unsigned char)ft_atoi(tmp[1]);
	color->b = (unsigned char)ft_atoi(tmp[2]);
	color->parsed = 1;
	free_2d_array(tmp);
}

void	get_game_data(t_data *data, char *line)
{
	// color
	if (*line == 'F')
		get_color(data, &data->colors.floor, line + 1);
	else if (*line == 'C')
		get_color(data, &data->colors.ceiling, line + 1);
	// xpm
	else if (*line == 'N' && line[1] == 'O')
		get_texture(data, &data->images.north, line + 2);
	else if (*line == 'W' && line[1] == 'E')
		get_texture(data, &data->images.west, line + 2);
	else if (*line == 'E' && line[1] == 'A')
		get_texture(data, &data->images.est, line + 2);
	else if (*line == 'S' && line[1] == 'O')
		get_texture(data, &data->images.south, line + 2);
	else
		exit_cub3d(data, MAP_LINE_FORMAT);
}
