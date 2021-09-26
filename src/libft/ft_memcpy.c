/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:32:25 by trobin            #+#    #+#             */
/*   Updated: 2021/09/21 16:38:54 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memcpy(char *dest, const char *src, int size)
{
	int	i;

	if (!src && !dest)
		return (0);
	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		++i;
	}
	return (dest);
}
