/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 10:17:20 by trobin            #+#    #+#             */
/*   Updated: 2021/09/21 16:48:34 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *s)
{
	long	result;

	result = 0;
	while (ft_isdigit(*s))
	{
		result = result * 10 + *s - 48;
		if (result > 2147483647)
			return (-1);
		s++;
	}
	return (result);
}
