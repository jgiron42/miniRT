/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:52:20 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 16:17:39 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**error protection OK :D
*/

void	ft_minirt(t_all_info all_info)
{
	t_pix	pixel;
	char	*img_addr;
	int		color;
	t_pix	original_dim;

	original_dim = all_info.scene_info.dim;
	if (all_info.scene_info.zoom % 2 == 1)
		all_info.scene_info.dim = (t_pix){
		200,
		200
	};
	img_addr = ft_get_img_address(all_info.img_ptr, 24,
			all_info.scene_info.dim.i, 1);
	pixel.j = -1;
	while (++pixel.j < all_info.scene_info.dim.j && (pixel.i = -1) == -1)
		while (++pixel.i < all_info.scene_info.dim.i)
		{
			color = ft_stereo(all_info, pixel);
			ft_memcpy(img_addr + pixel.j * all_info.scene_info.dim.i *
			4 + pixel.i * 4, &color, 4);
		}
	all_info.scene_info.dim = original_dim;
	if (all_info.scene_info.zoom % 2 == 1)
		ft_zoom(all_info, img_addr);
}

void	ft_pixel_calc2(t_all_info *all_info, double factor, t_coord *y_vect,
					t_coord *fov_vector)
{
	(*y_vect) = (t_coord){
			(*y_vect).x * factor,
			(*y_vect).y * factor,
			(*y_vect).z * factor
	};
	(*fov_vector) = ft_unit_vect((*all_info).cameras->vect);
	factor = 1 / cos((*all_info).cameras->length / 2);
	(*fov_vector) = (t_coord){
			(*fov_vector).x * factor,
			(*fov_vector).y * factor,
			(*fov_vector).z * factor
	};
}

t_coord	original_vector(t_all_info all_info, t_pix pixel)
{
	double		factor;
	t_coord		x_vect;
	t_coord		y_vect;
	t_coord		fov_vector;

	x_vect = all_info.cameras->vect.x == 0 && all_info.cameras->vect.y == 0 ?
ft_coord(0, 1, 0) : ft_unit_vect(ft_vector_rotation(ft_coord(
all_info.cameras->vect.x, all_info.cameras->vect.y, 0),
		ft_coord(0, 0, 1), M_PI_2));
	y_vect = all_info.cameras->vect.x == 0 && all_info.cameras->vect.y == 0 ?
ft_coord(1, 0, 0) : ft_unit_vect(ft_vector_rotation(x_vect,
		all_info.cameras->vect, M_PI_2));
	factor = (((double)pixel.i * 2) - (double)all_info.scene_info.dim.i) /
			all_info.scene_info.dim.i;
	x_vect = (t_coord){
		x_vect.x * factor,
		x_vect.y * factor,
		x_vect.z * factor
	};
	factor = ((-((double)pixel.j * 2) + (double)all_info.scene_info.dim.j) /
		all_info.scene_info.dim.j) * ((double)all_info.scene_info.dim.j /
							(double)all_info.scene_info.dim.i);
	ft_pixel_calc2(&all_info, factor, &y_vect, &fov_vector);
	return (ft_unit_vect(ft_coord_addition(ft_coord_addition(x_vect, y_vect),
			fov_vector)));
}

t_color	getcolor(t_all_info *all_info, t_color *result)
{
	(*result).r = (*result).r > 255 ? 255 : (*result).r;
	(*result).g = (*result).g > 255 ? 255 : (*result).g;
	(*result).b = (*result).b > 255 ? 255 : (*result).b;
	(*result).r *= (*all_info).scene_info.fi.r == 0 ? 0 : 255 /
												(*all_info).scene_info.fi.r;
	(*result).g *= (*all_info).scene_info.fi.g == 0 ? 0 : 255 /
												(*all_info).scene_info.fi.g;
	(*result).b *= (*all_info).scene_info.fi.b == 0 ? 0 : 255 /
												(*all_info).scene_info.fi.b;
	return (*result);
}

t_color	ft_pixel_calc(t_all_info all_info, t_pix pixel, t_mrt_list *objects)
{
	t_coord		vect;
	double		tmp1;
	t_mrt_list	*tmp2;
	t_color		result;

	tmp1 = MAXFLOAT;
	tmp2 = NULL;
	vect = original_vector(all_info, pixel);
	result = ft_skysphere(all_info, vect);
	while (objects)
	{
		if (!isnan(ft_intersection(vect, all_info.cameras->pos, *objects).x) &&
			ft_dist(all_info.cameras->pos, ft_intersection(vect,
					all_info.cameras->pos, *objects)) < tmp1 - PRECISION)
		{
			tmp1 = ft_dist(all_info.cameras->pos, ft_intersection(vect,
					all_info.cameras->pos, *objects));
			tmp2 = objects;
		}
		objects = objects->next;
	}
	if (tmp2)
		result = ft_luminosity(all_info, *tmp2, vect);
	result = getcolor(&all_info, &result);
	return (result);
}
