/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:06:33 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/14 15:50:34 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl_linedup(char *tmp, char *buff)
{
	int		n;
	char	*result;

	n = 0;
	free(buff);
	if (!tmp)
		return (NULL);
	while (tmp[n] && tmp[n] != '\n')
		n++;
	if (!(result = malloc(n + 1)))
		return (NULL);
	result[n] = 0;
	while (--n >= 0)
		result[n] = tmp[n];
	return (result);
}

int		get_next_line(int fd, char **line)
{
	static char	*tmp;
	char		*buff;
	int			ret;
	char		*old;

	if ((ret = 1) && (read(fd, NULL, 0) == -1 || !line || BUFFER_SIZE < 1))
		return (-1);
	if (!(buff = malloc(BUFFER_SIZE + 1)))
		return (0);
	if (!tmp)
		if (!(tmp = malloc(BUFFER_SIZE + 1)) ||
		(*tmp = 0))
			return (0);
	while (!ft_gnl_strchr(old = tmp, '\n') && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		tmp = ft_gnl_strjoin(tmp, buff, ret);
		free(old);
	}
	*line = ft_gnl_linedup(tmp, buff);
	ret = ft_gnl_strchr(tmp, '\n') ? 1 : ret;
	tmp = ft_gnl_strchr(tmp, '\n') ?
			ft_gnl_strdup((ft_gnl_strchr(tmp, '\n') + 1)) : NULL;
	free(old);
	return (ret);
}
