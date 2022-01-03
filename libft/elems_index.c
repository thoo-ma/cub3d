/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:26:34 by trobin            #+#    #+#             */
/*   Updated: 2021/10/09 17:26:44 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	elems_index(char *s1, char *s2)
{
	int	i;
	int	index;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i])
		{
			index = elem_index(s2, s1[i]);
			if (index > -1)
				return (elem_index(s1, s2[index]));
			i++;
		}
	}
	return (-1);
}
