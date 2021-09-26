/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:29:14 by trobin            #+#    #+#             */
/*   Updated: 2021/09/21 16:39:19 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return index of the first character of `s` which is not in `rejected`
**
*/

int	ft_strcspn(const char *s, const char *rejected)
{
	int	len;

	len = 0;
	while (*s && ft_strchr(rejected, *s))
		++s;
	while (*s && !ft_strchr(rejected, *s))
	{
		++s;
		++len;
	}
	return (len);
}
