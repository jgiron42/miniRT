/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:25:18 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 18:39:06 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**error protection OK :D
*/

void		ft_square_intersection2(t_mrt_list *object, t_coord *point,
		t_coord *vect1, t_coord *vect2)
{
	(*vect2) = ft_unit_vect(ft_vector_rotation((*vect1),
			(*object).vect, M_PI_2));
	(*vect1).x *= (*object).length;
	(*vect1).y *= (*object).length;
	(*vect1).z *= (*object).length;
	(*vect2).x *= (*object).length;
	(*vect2).y *= (*object).length;
	(*vect2).z *= (*object).length;
	point[0] = ft_coord_addition((*vect1), (*vect2));
	point[1] = ft_coord_addition((*vect1), ft_vect_calc((*vect2),
			(t_coord){0}));
	point[2] = ft_coord_addition(ft_vect_calc((*vect1), (t_coord){0}),
			ft_vect_calc((*vect2), (t_coord){0}));
	point[3] = ft_coord_addition(ft_vect_calc((*vect1), (t_coord){0}),
			(*vect2));
}

int			ft_square_intersection(t_mrt_list object, t_coord intersection)
{
	t_coord	point[4];
	t_coord	vect1;
	t_coord	vect2;

	if (object.vect.x == 0 && object.vect.y == 0)
		vect1 = (t_coord){1, 0, 0};
	else if (object.vect.z == 0)
		vect1 = (t_coord) {
				.z = 1};
	else
		vect1 = ft_unit_vect(ft_vector_rotation(object.vect,
	ft_vector_rotation(ft_coord(object.vect.x, object.vect.y, 0),
	ft_coord(0, 0, 1), M_PI_2), M_PI_2));
	ft_square_intersection2(&object, point, &vect1, &vect2);
	return (ft_scalar(object.vect, ft_vect_product(ft_vect_calc(*point,
*(point + 1)), ft_vect_calc(*point, intersection))) < 0 && ft_scalar(
object.vect, ft_vect_product(ft_vect_calc(*(point + 1), *(point + 2)),
ft_vect_calc(*(point + 1), intersection))) < 0 && ft_scalar(object.vect,
ft_vect_product(ft_vect_calc(*(point + 2), *(point + 3)), ft_vect_calc(
*(point + 2), intersection))) < 0 && ft_scalar(object.vect, ft_vect_product(
ft_vect_calc(*(point + 3), *point), ft_vect_calc(*(point + 3), intersection
))) < 0);
}

t_coord		ft_plane_intersection(t_coord vect, t_coord origin,
		t_mrt_list object)
{
	double	t;
	t_coord	result;

	if (object.id == TRIANGLE)
		object.vect = ft_unit_vect(ft_vect_product(ft_vect_calc(
*object.polygon, *(object.polygon + 1)), ft_vect_calc(*object.polygon,
		*(object.polygon + 2))));
	t = -((object.vect.x * (origin.x - object.pos.x) + object.vect.y * (origin.y
	- object.pos.y) + object.vect.z * (origin.z - object.pos.z)) / (vect.x *
		object.vect.x + vect.y * object.vect.y + vect.z * object.vect.z));
	result.x = origin.x + t * vect.x;
	result.y = origin.y + t * vect.y;
	result.z = origin.z + t * vect.z;
	if (t > 0 && ((object.id == PLANE) ||
			(object.id == DISK && ft_dist(object.pos, result) <= object.radius)
	|| (object.id == TRIANGLE && ft_scalar(object.vect, ft_vect_product(
ft_vect_calc(*object.polygon, *(object.polygon + 1)), ft_vect_calc(
*object.polygon, result))) > PRECISION && ft_scalar(object.vect,
ft_vect_product(ft_vect_calc(*(object.polygon + 1), *(object.polygon + 2
)), ft_vect_calc(*(object.polygon + 1), result))) > PRECISION && ft_scalar(
object.vect, ft_vect_product(ft_vect_calc(*(object.polygon + 2),
*object.polygon), ft_vect_calc(*(object.polygon + 2), result))) > PRECISION)
	|| (object.id == SQUARE && ft_square_intersection(object, result))))
		return (result);
	return ((t_coord){NAN, NAN, NAN});
}

t_coord		ft_intersection(t_coord vect, t_coord origin, t_mrt_list object)
{
	t_coord		result;

	result = (t_coord){
			.x = NAN,
			.y = NAN,
			.z = NAN
	};
	if (object.id == SPHERE)
		result = ft_sphere_intersection(vect, origin, object);
	else if (object.id == CYLINDER)
		result = ft_cylinder_intersection(vect, origin, object);
	else if (object.id == SQUARE || object.id == PLANE || object.id == DISK ||
	object.id == TRIANGLE)
		result = ft_plane_intersection(vect, origin, object);
	if (ft_dist(origin, result) < 0.000001)
		result = (t_coord){
				.x = NAN,
				.y = NAN,
				.z = NAN
		};
	return (result);
}
