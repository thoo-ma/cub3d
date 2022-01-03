/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:48:59 by trobin            #+#    #+#             */
/*   Updated: 2022/01/03 19:42:29 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int		ft_isdigit(int c);
int		ft_strlen(const char *s);
void	ft_bzero(char *s, int n);
void	*ft_memchr(const void *s, int c, int n);
char	*ft_memcpy(char *dest, const char *src, int size);
char	*ft_strpbrk(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strpbrk(char *s1, char *s2);
char	*ft_strdup(const char *s);
int		ft_strncat(char **dest, char *src, int n);
int		ft_strcspn(const char *s, const char *rejected);
char	*ft_strcpy(char *dest, char *src, int n);
char	*ft_strndup(char *src, int n);
int		ft_atoi(char *s);
char	**ft_split(char *s, char c);
void	*ft_memset(void *addr, int value, int n);
int		ft_strcmp(char *s1, char *s2);
int		ft_strptrlen(void **s);
int		elem_index(char *s, char c);
int		elems_index(char *s1, char *s2);

#endif
