/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_anti_aliasing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:13:13 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 16:28:47 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**error protection OK :D
*/

static t_color	getcolor(t_all_info *all_info, t_pix *pixel, t_color *result)
{
	int		dim;
	t_pix	index;

	dim = sqrt((*all_info).scene_info.anti_aliasing);
	(*all_info).scene_info.dim.i *= dim;
	(*all_info).scene_info.dim.j *= dim;
	index.j = dim;
	while (--index.j >= 0)
	{
		index.i = dim;
		while (--index.i >= 0)
		{
			(*result) = ft_color_addition((*result),
					ft_pixel_calc((*all_info), (t_pix) {
				dim * (*pixel).i - (dim / 2) + index.i,
				dim * (*pixel).j - (dim / 2) + index.j
				}, (*all_info).objects));
		}
	}
	(*result) = (t_color){
			(*result).r / (*all_info).scene_info.anti_aliasing,
			(*result).g / (*all_info).scene_info.anti_aliasing,
			(*result).b / (*all_info).scene_info.anti_aliasing,
	};
	return (*result);
}

t_color			ft_anti_aliasing(t_all_info all_info, t_pix pixel)
{
	t_color	result;

	result = (t_color){0};
	if (all_info.scene_info.anti_aliasing == 0 ||
	all_info.scene_info.zoom % 2 == 1)
		result = ft_pixel_calc(all_info, pixel, all_info.objects);
	else
		result = getcolor(&all_info, &pixel, &result);
	return (result);
}
