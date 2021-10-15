/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:47:53 by trobin            #+#    #+#             */
/*   Updated: 2021/10/15 15:59:06 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_file_extension(t_data *data, char *filename)
{
	size_t	len;

	len = 0;
	len = ft_strlen(filename);
	if (len < 5 || ft_strcmp(&filename[len - 4], ".cub"))
	{
		exit_cub3d(data, MAP_EXTENSION);
	}
}

static int	open_map(t_data *data, char *filename)
{
	int	fd;

	fd = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			exit_cub3d(data, MAP_ENOENT);
		else if (errno == EACCES)
			exit_cub3d(data, MAP_EACCES);
		else
			exit_cub3d(data, MAP_OPEN);
	}
	return (fd);
}

static void	check_game_data(t_data *data)
{
	if (!data->images.est.img
		|| !data->images.west.img
		|| !data->images.north.img
		|| !data->images.south.img)
		exit_cub3d(data, XPM_MISSING);
	if (data->images.est.ll != 256
		|| data->images.west.ll != 256
		|| data->images.north.ll != 256
		|| data->images.south.ll != 256)
		exit_cub3d(data, XPM_SIZE);
	if (!data->colors.floor.parsed
		|| !data->colors.ceiling.parsed)
		exit_cub3d(data, COLOR_MISSING);
}

void	parse(t_data *data, char *filename)
{
	int		fd;
	char	*line;

	check_file_extension(data, filename);
	fd = open_map(data, filename);
	line = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!*line)
			;
		else if (!ft_strcspn(line, " 01"))
		{
			get_map(data, fd, &line);
			break ;
		}
		else
			get_game_data(data, line);
		free(line);
	}
	close(fd);
	check_game_data(data);
	check_map(data);
	get_mlx_window(data);
	get_mlx_image(data);
	raycasting(data);
}
