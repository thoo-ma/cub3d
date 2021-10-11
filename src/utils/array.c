/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:53:10 by trobin            #+#    #+#             */
/*   Updated: 2021/10/11 19:14:45 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	length_2d_array(char **a)
{
	int	i;

	i = -1;
	if (a)
	{
		i = 0;
		while (a[i])
		{
			i++;
		}
	}
	return (i);
}

void	free_2d_array(char **a)
{
	int	i;

	i = 0;
	if (a)
	{
		while (a[i])
		{
			free(a[i]);
			i++;
		}
		free(a);
	}
}

void	print_2d_array(char **a)
{
	int	i;

	i = 0;
	if (a)
	{
		while (a[i])
		{
			printf("%s\n", a[i]);
			i++;
		}
	}
}

void	skip_digits(char **s)
{
	while (ft_isdigit(**s))
		(*s)++;
}

void	skip_spaces(char **s)
{
	while (**s == ' ')
		(*s)++;
}
