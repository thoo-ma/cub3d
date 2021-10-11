/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:41:51 by trobin            #+#    #+#             */
/*   Updated: 2021/10/09 16:04:48 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int	elem(char *s, char c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		++i;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

int	ft_strncat(char **dest, char *src, int n)
{
	char	*temp;
	int		dest_len;

	if (!dest || !src || !*src)
		return (1);
	dest_len = ft_strlen(*dest);
	temp = 0;
	temp = malloc(sizeof(char) * (dest_len + n + 1));
	if (!temp)
		return (-1);
	ft_memcpy(temp, *dest, dest_len);
	ft_memcpy((temp + dest_len), src, n);
	temp[dest_len + n] = '\0';
	free(*dest);
	*dest = temp;
	return (1);
}

int	temp_to_line(char **line, char *temp, char *buffer, int lf)
{
	*line = ft_strdup(temp);
	if (temp)
		free(temp);
	if (*line == 0)
		return (-1);
	if (lf > -1)
	{
		ft_memcpy(buffer, (buffer + lf + 1), (BUFFER_SIZE - lf));
		ft_bzero((buffer + BUFFER_SIZE - lf), (lf + 1));
		return (1);
	}
	else
	{
		ft_bzero(buffer, BUFFER_SIZE);
		if (**line)
			return (1);
		return (0);
	}
}

int	get_next_line(int fd, char **line)
{
	char		*temp;
	int			ret;
	int			lf;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	temp = 0;
	lf = elem(buffer, '\n');
	while (lf == -1)
	{
		if (ft_strncat(&temp, buffer, BUFFER_SIZE) == -1)
			return (-1);
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
			return (-1);
		buffer[ret] = '\0';
		if (ret == 0)
			break ;
		lf = elem(buffer, '\n');
	}
	if (lf > -1)
		if (ft_strncat(&temp, buffer, lf) == -1)
			return (-1);
	return (temp_to_line(line, temp, buffer, lf));
}
