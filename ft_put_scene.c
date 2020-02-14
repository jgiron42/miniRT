/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:39:09 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/14 15:21:29 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**error protection OK :D
*/

int		ft_red_cross(t_all_info *all_info)
{
	ft_quit(*all_info, 0);
	return (0);
}

int		get_element_number(t_mrt_list *list)
{
	static t_mrt_list	*first_element;
	int					result;
	t_mrt_list			*tmp;

	result = 1;
	if (!first_element)
		first_element = list;
	tmp = first_element;
	while (tmp != list && tmp->next)
	{
		tmp = tmp->next;
		result++;
	}
	return (result);
}

void	ft_put_hud(t_all_info all_info, char *object_str)
{
	char	*tmp;

	if (!(tmp = ft_itoa(get_element_number(all_info.cameras))))
		ft_quit(all_info, ERR_SYS);
	mlx_string_put(all_info.mlx_ptr, all_info.win_ptr, 7, 15, HUD_COLOR,
			"camera");
	mlx_string_put(all_info.mlx_ptr, all_info.win_ptr, 57, 15, HUD_COLOR, tmp);
	free(tmp);
	if (!(tmp = ft_itoa((all_info.cameras->length / M_PI) * 180)))
		ft_quit(all_info, ERR_SYS);
	mlx_string_put(all_info.mlx_ptr, all_info.win_ptr, 7, 30, HUD_COLOR,
			"FOV:");
	mlx_string_put(all_info.mlx_ptr, all_info.win_ptr, 40, 30, HUD_COLOR, tmp);
	free(tmp);
	mlx_string_put(all_info.mlx_ptr, all_info.win_ptr, 7, 45, HUD_COLOR,
		all_info.scene_info.mode % 2 == 1 ? "Edit mode" : "View mode");
	mlx_string_put(all_info.mlx_ptr, all_info.win_ptr, 7, 60, HUD_COLOR,
			object_str);
}

void	ft_put_scene(t_all_info all_info, char *object_str)
{
	if (!object_str)
		ft_quit(all_info, ERR_SYS);
	if (!all_info.win_ptr)
		all_info.win_ptr = mlx_new_window(all_info.mlx_ptr,
all_info.scene_info.dim.i, all_info.scene_info.dim.j, all_info.program_name);
	ft_minirt(all_info);
	mlx_put_image_to_window(all_info.mlx_ptr, all_info.win_ptr, all_info.img_ptr
			, 0, 0);
	if (all_info.scene_info.dim.i > 500 && all_info.scene_info.dim.j > 500)
		ft_put_hud(all_info, object_str);
	free(object_str);
	mlx_key_hook(all_info.win_ptr, &ft_keyboard_interaction, &all_info);
	mlx_hook(all_info.win_ptr, 17, (1L << 17), &ft_red_cross,
			&all_info);
	mlx_loop(all_info.mlx_ptr);
}
