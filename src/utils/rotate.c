/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 09:18:57 by trobin            #+#    #+#             */
/*   Updated: 2021/09/24 17:17:22 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double		rotate(double ray, double angle)
{
	double ret;

	ret = ray + angle;
	while (ret >= 2 * M_PI)
		ret -= 2 * M_PI;
	while (ret < 0)
		ret += 2 * M_PI;
	return (ret);
}
