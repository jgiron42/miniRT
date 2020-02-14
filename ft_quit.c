/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:55:46 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/14 15:33:43 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**error protection OK :D
*/

void	ft_free_mrt_list(t_mrt_list *list)
{
	t_mrt_list	**current;

	while (list->next)
	{
		current = &list;
		while ((*current)->next)
			*current = (*current)->next;
		if ((*current)->polygon)
			free((*current)->polygon);
		free((*current)->next);
		(*current)->next = NULL;
	}
	free(list);
}

void	ft_free_all(t_all_info all_info)
{
	ft_free_mrt_list(all_info.cameras);
	ft_free_mrt_list(all_info.lights);
	ft_free_mrt_list(all_info.objects);
	if (all_info.program_name)
		free(all_info.program_name);
	if (all_info.img_ptr)
		mlx_destroy_image(all_info.mlx_ptr, all_info.img_ptr);
	if (all_info.scene_info.skysphere.img_ptr)
		mlx_destroy_image(all_info.mlx_ptr,
				all_info.scene_info.skysphere.img_ptr);
	if (all_info.win_ptr)
		mlx_destroy_window(all_info.mlx_ptr, all_info.win_ptr);
}

int		ft_error(int error)
{
	int	ret;

	ret = 0;
	if (error == ERR_SYS)
		perror("Error \n");
	else if (error == MLX_ERR)
		ret = write(2, "Error \nMinilibx error\n", 22);
	else if (error == FILE_ERR)
		ret = write(2, "Error \nFile not well formated\n", 30);
	else if (error == ARG_ERR)
		ret = write(2,
		"Error \nWrong syntax\nUsage: MiniRT file.rt [-save [path]]\n",
		57);
	if (ret == -1)
		perror("Error\n");
	while(1){}
	return (error == 0 ? 0 : 1);
}

void	ft_quit(t_all_info all_info, int error)
{
	ft_free_all(all_info);
	exit(ft_error(error));
}
