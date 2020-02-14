/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stereo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:09:12 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/13 18:35:58 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**error protection OK :D
*/

void	ft_stereo2(t_all_info *all_info, t_coord *tmp, double *angle)
{
	(*tmp) = ft_unit_vect(ft_vector_rotation(
ft_coord((*all_info).cameras->vect.x, (*all_info).cameras->vect.y, 0),
ft_coord(0, 0, 1), M_PI_2));
	(*tmp).x *= (*all_info).scene_info.stereo / 2;
	(*tmp).y *= (*all_info).scene_info.stereo / 2;
	(*angle) = -atan(((*all_info).scene_info.stereo / 2) /
					(*all_info).scene_info.stereo_depth);
	(*all_info).cameras->pos = ft_coord_addition((*all_info).cameras->pos,
			(*tmp));
	(*all_info).cameras->vect = ft_vector_rotation((*all_info).cameras->vect,
						ft_coord(0, 0, 1), (*angle));
}

int		ft_stereo(t_all_info all_info, t_pix pixel)
{
	t_coord		tmp;
	t_color		result1;
	t_color		result2;
	double		angle;

	if (all_info.scene_info.stereo == 0)
	{
		result1 = ft_anti_aliasing(all_info, pixel);
		return ((int)((result1.r << 16) + (result1.g << 8) + result1.b));
	}
	ft_stereo2(&all_info, &tmp, &angle);
	result1 = ft_anti_aliasing(all_info, pixel);
	all_info.cameras->pos = ft_vect_calc(tmp,
								ft_vect_calc(tmp, all_info.cameras->pos));
	all_info.cameras->vect = ft_vector_rotation(all_info.cameras->vect,
						ft_coord(0, 0, 1), -2 * angle);
	result2 = ft_anti_aliasing(all_info, pixel);
	all_info.cameras->vect = ft_vector_rotation(all_info.cameras->vect,
									ft_coord(0, 0, 1), angle);
	all_info.cameras->pos = ft_coord_addition(all_info.cameras->pos, tmp);
	return ((int)(((result1.r / 2) << 16) + ((result2.g / 2) << 8) +
	result2.b / 2));
}
