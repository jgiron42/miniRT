/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_luminosity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 14:51:54 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 21:42:35 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	cylinder_normal(t_mrt_list *object, t_coord *point,
		t_all_info *all_info)
{
	t_coord	result;
	double	length;

	(*object).vect = ft_unit_vect((*object).vect);
	result = ft_vect_calc((*object).pos, (*point));
	length = sqrt((ft_dist((*object).pos, (*point)) * ft_dist((*object).pos,
			(*point))) - ((*object).radius * (*object).radius));
	if (ft_scalar((*object).vect, result) > 0)
	{
		result.x -= (*object).vect.x * length;
		result.y -= (*object).vect.y * length;
		result.z -= (*object).vect.z * length;
	}
	else if (ft_scalar((*object).vect, result) < 0)
	{
		result.x += (*object).vect.x * length;
		result.y += (*object).vect.y * length;
		result.z += (*object).vect.z * length;
	}
	result = ft_unit_vect(result);
	if (ft_scalar(result, ft_vect_calc((*all_info).cameras->pos, (*point))) < 0)
		return (result);
	else
		return (ft_vect_calc(result, (t_coord){0, 0, 0}));
}

/*
**error protection OK :D
*/

t_coord	ft_normal_vector(t_mrt_list object, t_coord point, t_all_info all_info)
{
	if (object.id == PLANE || object.id == SQUARE || object.id == DISK)
	{
		return (ft_scalar(ft_vect_calc(point, all_info.cameras->pos),
				object.vect) > 0 ? object.vect : ft_vect_calc(
				object.vect, (t_coord) {0, 0, 0}));
	}
	else if (object.id == SPHERE)
		return (ft_dist(object.pos, all_info.cameras->pos) > object.radius
				? ft_vect_calc(object.pos, point) :
				ft_vect_calc(point, object.pos));
	else if (object.id == TRIANGLE)
	{
		object.vect = ft_unit_vect(ft_vect_product(
				ft_vect_calc(*object.polygon, *(object.polygon + 1)),
				ft_vect_calc(*object.polygon, *(object.polygon + 2))));
		return (ft_scalar(ft_vect_calc(point, all_info.cameras->pos),
					object.vect) > 0 ? object.vect : ft_vect_calc(
				object.vect, (t_coord) {0, 0, 0}));
	}
	return (cylinder_normal(&object, &point, &all_info));
}

void	ft_luminosity2(t_color *color, t_all_info all_info, t_mrt_list object,
		t_coord point)
{
	double	factor;
	t_coord	normal_vect;
	t_coord	light_vect;

	light_vect = ft_unit_vect(ft_vect_calc(all_info.lights->pos, point));
	normal_vect = ft_unit_vect(ft_normal_vector(object, point, all_info));
	factor = -ft_scalar(light_vect, normal_vect);
	if (factor > 0)
	{
		*color = (t_color){
			.r = color->r + ((double)object.color.r / 255) *
					all_info.lights->color.r * factor * all_info.lights->light,
			.g = color->g + ((double)object.color.g / 255) *
					all_info.lights->color.g * factor * all_info.lights->light,
			.b = color->b + ((double)object.color.b / 255) *
					all_info.lights->color.b * factor * all_info.lights->light
		};
	}
}

char	ft_luminosity3(t_all_info *all_info, t_mrt_list *objects,
		t_coord *point, t_coord *tmp)
{
	char is_lighted;

	is_lighted = 1;
	while (objects)
	{
		(*tmp) = ft_intersection(ft_vect_calc((*point),
				(*all_info).lights->pos), (*point), *objects);
		if (!isnan((*tmp).x) && ft_dist((*tmp), (*point)) < ft_dist(
				(*all_info).lights->pos, (*point)) - PRECISION)
		{
			is_lighted = 0;
			break ;
		}
		objects = objects->next;
	}
	return (is_lighted);
}

t_color	ft_luminosity(t_all_info all_info, t_mrt_list current,
					t_coord original_vector)
{
	t_mrt_list	*objects;
	t_coord		point;
	t_coord		tmp;
	char		is_lighted;
	t_color		result;

	point = ft_intersection(original_vector, all_info.cameras->pos, current);
	result = (t_color){
			(int)((double)current.color.r * (((double)
	all_info.scene_info.color.r / 255) * (double)all_info.scene_info.light)),
			(int)((double)current.color.g * (((double)
	all_info.scene_info.color.g / 255) * (double)all_info.scene_info.light)),
			(int)((double)current.color.b * (((double)
	all_info.scene_info.color.b / 255) * (double)all_info.scene_info.light)),
	};
	while (all_info.lights)
	{
		objects = all_info.objects;
		is_lighted = ft_luminosity3(&all_info, objects, &point, &tmp);
		if (is_lighted)
			ft_luminosity2(&result, all_info, current, point);
		all_info.lights = all_info.lights->next;
	}
	return (result);
}
