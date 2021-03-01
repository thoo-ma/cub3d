/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:33:23 by trobin            #+#    #+#             */
/*   Updated: 2021/09/22 16:12:14 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len;

	if (s == 0) // modif
		return (0); // modif
	len = ft_strlen(s);
	dest = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == 0)
		return (0);
	ft_memcpy(dest, s, len);
	dest[len] = '\0';
	return (dest);
}
