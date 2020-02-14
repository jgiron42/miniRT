/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 21:43:04 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/13 18:15:10 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** error protection OK :D
*/

void	ft_zoom(t_all_info all_info, char *img_addr)
{
	t_pix pixel;

	pixel.j = all_info.scene_info.dim.j;
	while (--pixel.j >= 0)
	{
		pixel.i = all_info.scene_info.dim.i;
		while (--pixel.i >= 0)
			ft_memcpy(img_addr + pixel.j * all_info.scene_info.dim.i * 4 +
			pixel.i * 4, img_addr + (200 * pixel.j /
			all_info.scene_info.dim.j) * 200 * 4 + (200 * pixel.i /
			all_info.scene_info.dim.i) * 4, 4);
	}
}
