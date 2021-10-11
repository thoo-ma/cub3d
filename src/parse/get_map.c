/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:45:02 by trobin            #+#    #+#             */
/*   Updated: 2021/10/11 19:23:12 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	try_ft_strncat(t_data *data, char **dst, char *src, int n)
{
	if (ft_strncat(dst, src, n) == -1)
	{
		if (src)
			free(src);
		if (*dst)
			free(*dst);
		exit_cub3d(data, MAP_FT_STRNCAT);
	}
}

void	safe_free(void **a)
{
	if (a && *a)
	{
		free(*a);
		*a = 0;
	}
}

void	get_map(t_data *data, int fd, char **line)
{
	char	*tmp;

	tmp = 0;
	while (*line)
	{
		if (**line)
		{
			try_ft_strncat(data, &tmp, *line, ft_strlen(*line));
			try_ft_strncat(data, &tmp, "\n", 1);
			safe_free((void *)line);
		}
		else
		{
			safe_free((void *)&tmp);
			safe_free((void *)line);
			exit_cub3d(data, MAP_DUPLICATE);
		}
		get_next_line(fd, line);
	}
	data->map = ft_split(tmp, '\n');
	safe_free((void *)&tmp);
	safe_free((void *)line);
	if (!data->map)
		exit_cub3d(data, MAP_FT_SPLIT);
}
