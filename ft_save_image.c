/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 19:53:18 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 21:01:30 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** error protection OK :D
*/

char	*ft_find_file_name(char *path)
{
	int	i;

	i = -1;
	while (path[++i])
		if (path[i] == '/')
		{
			path += i + 1;
			i = 0;
		}
	if (ft_strnstr(path, ".", ft_strlen(path)))
		*ft_strnstr(path, ".", ft_strlen(path)) = 0;
	return (ft_strdup(path));
}

int		ft_put_number_fd(int fd, int size, unsigned int nbr,
		t_all_info all_info)
{
	unsigned char	c;
	int				i;

	i = -1;
	while (++i < size)
	{
		c = (unsigned char)(nbr >> (i * 8));
		if (write(fd, &c, 1) == -1)
			ft_quit(all_info, ERR_SYS);
	}
	return (0);
}

void	ft_put_header(t_all_info all_info, int fd)
{
	if (write(fd, "BM", 2) == -1)
		ft_quit(all_info, ERR_SYS);
	ft_put_number_fd(fd, 4, all_info.scene_info.dim.i *
	all_info.scene_info.dim.i * 3 + 54, all_info);
	if (write(fd, "\0\0\0\0\x36\0\0\0\x28\0\0\0", 12) == -1)
		ft_quit(all_info, ERR_SYS);
	ft_put_number_fd(fd, 4, all_info.scene_info.dim.i, all_info);
	ft_put_number_fd(fd, 4, all_info.scene_info.dim.j, all_info);
	if (write(fd, "\1\0\x18\0\0\0\0\0", 8) == -1)
		ft_quit(all_info, ERR_SYS);
	ft_put_number_fd(fd, 4, all_info.scene_info.dim.i *
	all_info.scene_info.dim.i * 3, all_info);
	if (write(fd, "\xC4\x0E\0\0\xC4\x0E\0\0\0\0\0\0\0\0\0\0", 16) == -1)
		ft_quit(all_info, ERR_SYS);
}

void	ft_save_image(t_all_info all_info, int argc, char **argv, int n)
{
	char	*pathname;
	int		fd;
	t_pix	pixel;
	char	*c;
	char	*img_addr;

	ft_minirt(all_info);
	pixel = (t_pix){0, 0};
	if (!(pathname = ft_find_pathname(argc, argv, n, all_info)))
		ft_quit(all_info, ERR_SYS);
	fd = open(pathname, O_WRONLY | O_CREAT, 0666);
	img_addr = ft_get_img_address(all_info.img_ptr, 24,
			all_info.scene_info.dim.i, 1);
	ft_put_header(all_info, fd);
	while (++pixel.j <= all_info.scene_info.dim.j && (pixel.i = -1) == -1)
		while (++pixel.i < all_info.scene_info.dim.i)
		{
			c = (img_addr + (all_info.scene_info.dim.j - pixel.j) *
					all_info.scene_info.dim.i * 4 + pixel.i * 4);
			if (write(fd, c, 3) == -1)
				ft_quit(all_info, ERR_SYS);
		}
	free(pathname);
}

void	ft_save_all_image(t_all_info all_info, int argc, char **argv)
{
	int			n;
	t_mrt_list	*first_cam;

	if (ft_strncmp(argv[2], "-save", 5))
		ft_quit(all_info, ARG_ERR);
	n = all_info.cameras->next ? 1 : 0;
	first_cam = all_info.cameras;
	while (all_info.cameras)
	{
		ft_save_image(all_info, argc, argv, n);
		n++;
		all_info.cameras = all_info.cameras->next;
	}
	all_info.cameras = first_cam;
	ft_quit(all_info, 0);
}
