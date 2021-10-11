/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:33:23 by trobin            #+#    #+#             */
/*   Updated: 2021/10/09 16:02:09 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len;

	if (s == 0)
		return (0);
	len = ft_strlen(s);
	dest = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == 0)
		return (0);
	ft_memcpy(dest, s, len);
	dest[len] = '\0';
	return (dest);
}
