/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 10:54:42 by trobin            #+#    #+#             */
/*   Updated: 2021/09/21 16:49:12 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, int n)
{
	char	*dest;

	dest = 0;
	dest = malloc(sizeof(char) * n);
	if (!dest)
		return (0);
	return (ft_strcpy(dest, src, n));
}
