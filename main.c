/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:18:34 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 22:52:06 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**error protection OK :D
*/

int	main(int argc, char **argv)
{
	t_all_info	all_info;
	int			fd;

	all_info = (t_all_info){0};
	if (!(all_info.mlx_ptr = mlx_init()))
		ft_quit(all_info, MLX_ERR);
	if (argc == 1 || argc > 4)
		ft_quit(all_info, ARG_ERR);
	if (!(all_info.cameras = malloc(sizeof(t_mrt_list))) ||
		!(all_info.objects = malloc(sizeof(t_mrt_list))) ||
		!(all_info.lights = malloc(sizeof(t_mrt_list))))
		ft_quit(all_info, ERR_SYS);
	all_info.cameras->next = NULL;
	all_info.lights->next = NULL;
	all_info.objects->next = NULL;
	if ((fd = open(argv[1], O_RDONLY)) < 1)
		return (ft_quit(all_info, ERR_SYS));
	ft_list_init(fd, &all_info);
	if (!(all_info.img_ptr = mlx_new_image(all_info.mlx_ptr,
			all_info.scene_info.dim.i, all_info.scene_info.dim.j)))
		ft_quit(all_info, MLX_ERR);
	if (argc == 2)
		ft_put_scene(all_info, ft_strdup(""), argv[1]);
	ft_save_all_image(all_info, argc, argv);
}
