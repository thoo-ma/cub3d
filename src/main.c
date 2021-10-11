/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:20:13 by trobin            #+#    #+#             */
/*   Updated: 2021/10/11 19:42:18 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
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
	return (0);
}
