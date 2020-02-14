/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:18:34 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/14 15:37:53 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//error protection OK :D

int 	main(int argc, char ** argv)
{
	t_all_info	all_info;
	int 		fd;

	all_info = (t_all_info){};
	if (!(all_info.mlx_ptr = mlx_init()))
		ft_quit(all_info, MLX_ERR);
	fd = 0;
	if (!(all_info.cameras = malloc(sizeof(t_mrt_list))) ||
		!(all_info.objects = malloc(sizeof(t_mrt_list))) ||
		!(all_info.lights = malloc(sizeof(t_mrt_list))) ||
			(fd = open(argv[1], O_RDONLY)) < 1)
		ft_quit(all_info, ERR_SYS);
	ft_list_init(fd, &all_info);

	if (!(all_info.img_ptr = mlx_new_image(all_info.mlx_ptr,
			all_info.scene_info.dim.i, all_info.scene_info.dim.j)))
		ft_quit(all_info, MLX_ERR);
	if (argc == 2)
	{
		all_info.program_name = ft_find_file_name(argv[1]);
		ft_put_scene(all_info, ft_strdup(""));
	}
	else if (argc > 2)
		if(!ft_strncmp(argv[2], "-save", 5))
			ft_save_all_image(all_info, argc, argv);
	ft_quit(all_info, ARG_ERR);
}