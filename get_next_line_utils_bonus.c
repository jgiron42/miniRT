/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:48:45 by jgiron            #+#    #+#             */
/*   Updated: 2020/01/25 20:26:57 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnl_strlen(const char *str)
{
	size_t a;

	a = 0;
	if (!str)
		return (0);
	while (str[a] != '\0')
		a++;
	return (a);
}

char	*ft_gnl_strchr(char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s)
		return (NULL);
	if (*s == 0)
		return (NULL);
	while (s[i] != 0 && (s[i] != (char)c))
		i++;
	if (s[i] == 0 && (char)c != 0)
		return (NULL);
	ptr = (char *)s;
	c = 0;
	return (ptr + i);
}

char	*ft_gnl_strjoin(char const *s1, char *s2, int ret)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s1)
		return (ft_gnl_strdup((char *)s2));
	if (!s2)
		return (ft_gnl_strdup((char *)s1));
	s2[ret] = 0;
	i = 0;
	while (s1[i] != 0)
		i++;
	j = 0;
	while (s2[j])
		j++;
	if (!(dst = malloc(i + j + 1)))
		return (NULL);
	dst[i + j] = 0;
	while (--j + 1 > 0)
		dst[i + j] = s2[j];
	j++;
	while (--i + 1 > 0)
		dst[i + j] = s1[i];
	return (dst);
}

char	*ft_gnl_strdup(char *str)
{
	char	*dst;
	int		i;

	i = 0;
	while (str[i])
		i++;
	dst = malloc(i + 1);
	dst[i] = 0;
	while (--i >= 0)
		dst[i] = str[i];
	return (dst);
}
