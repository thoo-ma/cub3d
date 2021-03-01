/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrondi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 05:46:48 by trobin            #+#    #+#             */
/*   Updated: 2021/09/21 16:50:24 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
 *
 * input:  coordonnee x ou y d'un point en CUB_LENGTH
 * output: coordonnee x ou y de ce meme en SQUARE_LENGTH
 */

double	arrondi(double z)
{
	double	min;
	double	max;

	min = 0;
	max = 0;
	while (max < z)
	{
		max += CUB_LENGTH / SQUARE_LENGTH;
		min = max - CUB_LENGTH / SQUARE_LENGTH;
	}
	if (max - z < z - min)
		return (max);
	return (min);
}
