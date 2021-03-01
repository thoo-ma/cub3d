/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 10:57:41 by trobin            #+#    #+#             */
/*   Updated: 2021/09/07 10:44:10 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# define BUFFER_SIZE	8

int		ft_strncat(char **dest, char *src, int n);
int		temp_to_line(char **line, char *temp, char *buffer, int lf);
int		get_next_line(int fd, char **line);

#endif
