/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:20:13 by trobin            #+#    #+#             */
/*   Updated: 2021/09/23 16:39:46 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int main(int ac, char **av)
{
	t_data	data;

	init_cub3d(&data);
	if (ac == 2)
	{
		parse(&data, av[1]);
		define_hooks(&data);
		exit_cub3d(&data, 0);
	}
	else
	{
		exit_cub3d(&data, MAIN_ARG);
	}
}
