/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:55:07 by jgiron            #+#    #+#             */
/*   Updated: 2020/01/25 20:26:57 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_GET_NEXT_LINE_H
# define GET_NEXT_LINE_GET_NEXT_LINE_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t			ft_gnl_strlen(const char *str);
char			*ft_gnl_strjoin(const char *s1, char *s2, int ret);
char			*ft_gnl_strchr(char *s, int c);
int				get_next_line(int fd, char **line);
char			*ft_gnl_linedup(char *tmp, char *buff);
char			*ft_gnl_strdup(char *str);

#endif
