/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:25:18 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/13 16:02:31 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//error protection OK :D

double		ft_polynom_2(double a, double b, double c, int root)
{
	double	delta;

	delta = b * b - 4 * a * c;
	if (((root == 2 && delta == 0) || (root == 1 && delta >= 0)) && a != 0)
		return((-b - sqrt(delta)) / (2 * a));
	else if (root == 2 && delta > 0 && a != 0)
		return((-b + sqrt(delta)) / (2 * a));
	return (NAN);
}

t_coord		ft_sphere_intersection(t_coord vect, t_coord origin, t_mrt_list object)
{
	double	root1;
	double	root2;
	t_coord	result1;
	t_coord	result2;
//		((origin.x + t * vect.x) - object.pos.x) ^ 2 + ((origin.y + t * vect.) - object.pos.y) ^ 2 +((origin.z + t * vect.z) - object.pos.z) ^ 2 = r^2;
//		(origin.x - object.pos.x + t * vect.x ) ^ 2
//		(origin.x - object.pos.x) ^ 2 + 2 * (origin.x - object.pos.x) * (t * vect.x) + (t * vect.x) ^ 2
//		Ex = t ^ 2 * (vect.x ^ 2) + t * (vect.x * (origin.x - object.pos.x)) + (origin.x - object.pos.x) ^ 2
//		Ex + Ey + Ez = r^2
//		0 =   t ^ 2 *		(vect.x ^ 2 + vect.y ^ 2 + vect.z ^ 2)
//			+ t *			( vect.x * (origin.x - object.pos.x) + vect.* (origin.y - object.pos.y) + vect.z * (origin.z - object.pos.z))
//			+ 				(origin.x - object.pos.x) ^ 2 + (origin.y - object.pos.y) ^ 2 + (origin.z - object.pos.z) ^ 2 - r ^ 2

	root1 = ft_polynom_2((vect.x * vect.x + vect.y * vect.y + vect.z * vect.z),
					2 * (vect.x * (origin.x - object.pos.x) + vect.y * (origin.y - object.pos.y) + vect.z * (origin.z - object.pos.z)),
					(origin.x - object.pos.x) * (origin.x - object.pos.x) + (origin.y - object.pos.y) * (origin.y - object.pos.y) + (origin.z - object.pos.z) * (origin.z - object.pos.z) - object.radius * object.radius,
					1);
	root2 = ft_polynom_2((vect.x * vect.x + vect.y * vect.y + vect.z * vect.z),
					2 * (vect.x * (origin.x - object.pos.x) + vect.y * (origin.y - object.pos.y) + vect.z * (origin.z - object.pos.z)),
					(origin.x - object.pos.x) * (origin.x - object.pos.x) + (origin.y - object.pos.y) * (origin.y - object.pos.y) + (origin.z - object.pos.z) * (origin.z - object.pos.z) - object.radius * object.radius,
					2);
	result1.x = origin.x + root1 * vect.x;
	result1.y = origin.y + root1 * vect.y;
	result1.z = origin.z + root1 * vect.z;
	result2.x = origin.x + root2 * vect.x;
	result2.y = origin.y + root2 * vect.y;
	result2.z = origin.z + root2 * vect.z;
	if((((isnan(root1) || ft_dist(origin, result1) < PRECISION || root1 < PRECISION) && !isnan(root2)) || (!isnan(root2)  && ft_dist(origin, result2) < ft_dist(origin, result1))) && root2 > PRECISION && ft_dist(origin, result2) > PRECISION)
		return (result2);
	if((((isnan(root2) || ft_dist(origin, result2) < PRECISION || root2 < PRECISION) && !isnan(root1)) || (!isnan(root1)  && ft_dist(origin, result1) < ft_dist(origin, result2))) && root1 > PRECISION && ft_dist(origin, result1) > PRECISION)
		return (result1);
	return ((t_coord){
			.x = NAN
	});
}

t_coord		ft_cylinder_intersection(t_coord vect, t_coord origin, t_mrt_list object)
{
	double	root[2];
	t_coord	result[2];
	int 	i;

//		((origin.x + t * vect.x) - object.pos.x) ^ 2 + ((origin.y + t * vect.) - object.pos.y) ^ 2 +((origin.z + t * vect.z) - object.pos.z) ^ 2    -    ((object.vect.x * (origin.x + t * vect.x) + object.vect.y * (origin.y + t * vect.) + object.vect.z * (origin.z + t * vect.z)) ^ 2 / 																												(object.vect.x ^ 2 + object.vect.y ^ 2 + object.vect.z ^ 2)) = r^2
//																								(object.vect.x ^ 2 * origin.x + t^2 * object.vect.x * vect.x^2)		2 * object.vect.x * origin.x + 2 * object.vect.x * t * vect.

//		0 = t ^ 2	(((object.vect.x * vect.x * vect.x + object.vect.y * vect.y * vect.y + object.vect.z * vect.z * vect.z) / (object.vect.x * object.vect.x + object.vect.y * object.vect.y + object.vect.z * object.vect.z)) + (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z))
//			+ t *	(2 * ((object.vect.x * vect.x + object.vect.y * vect.y + object.vect.z * vect.z) / (object.vect.x * object.vect.x + object.vect.y * object.vect.y + object.vect.z * object.vect.z)) + ( vect.x * (origin.x - object.pos.x) + vect.* (origin.y - object.pos.y) + vect.z * (origin.z - object.pos.z))
//			+ 		((object.vect.x * object.vect.x * origin.x + 2 * object.vect.x * origin.x + object.vect.y * object.vect.y  * origin.y + 2 * object.vect.y * origin.y + object.vect.z * object.vect.z * origin.z + 2 * object.vect.z * origin.z) / (object.vect.x * object.vect.x + object.vect.y * object.vect.y + object.vect.z * object.vect.z)) + (origin.x - object.pos.x) * (origin.x - object.pos.x) + (origin.y - object.pos.y) * (origin.y - object.pos.y) + (origin.z - object.pos.z) * (origin.z - object.pos.z) - object.diameter * object.diameter
	i = -1;
	while (++i <= 1)
	{
		root[i] = ft_polynom_2(vect.x *  vect.x +  vect.y *  vect.y +  vect.z *  vect.z - (((object.vect.x *  vect.x + object.vect.y *  vect.y + object.vect.z *  vect.z) * (object.vect.x *  vect.x + object.vect.y *  vect.y + object.vect.z *  vect.z)) / (object.vect.x * object.vect.x + object.vect.y * object.vect.y + object.vect.z * object.vect.z)),
				2 * ( (origin.x - object.pos.x) *  vect.x +  (origin.y - object.pos.y) *  vect.y +  (origin.z - object.pos.z) *  vect.z) - ((2 * (object.vect.x *  (origin.x - object.pos.x) + object.vect.y *  (origin.y - object.pos.y) + object.vect.z *  (origin.z - object.pos.z)) * (object.vect.x *  vect.x + object.vect.y *  vect.y + object.vect.z *  vect.z)) / (object.vect.x * object.vect.x + object.vect.y * object.vect.y + object.vect.z * object.vect.z)),
				(origin.x - object.pos.x) *  (origin.x - object.pos.x) +  (origin.y - object.pos.y) *  (origin.y - object.pos.y) +  (origin.z - object.pos.z) *  (origin.z - object.pos.z) - (((object.vect.x *  (origin.x - object.pos.x) + object.vect.y *  (origin.y - object.pos.y) + object.vect.z *  (origin.z - object.pos.z)) * (object.vect.x *  (origin.x - object.pos.x) + object.vect.y *  (origin.y - object.pos.y) + object.vect.z *  (origin.z - object.pos.z))) / (object.vect.x * object.vect.x + object.vect.y * object.vect.y + object.vect.z * object.vect.z)) - object.radius * object.radius, i + 1);
		result[i].x = origin.x + root[i] * vect.x;
		result[i].y = origin.y + root[i] * vect.y;
		result[i].z = origin.z + root[i] * vect.z;
	}
	if((root[1] > 0 && (ft_dist(origin, result[0]) < PRECISION || isnan(root[0])) && !isnan(root[1])) || ((ft_dist(origin, result[1]) > PRECISION) && root[1] > 0 && (!isnan(root[1])  && ((root[0] < 0 || (ft_dist(origin, result[1]) < ft_dist(origin, result[0]) || ft_dist(object.pos, result[0]) > hypot(object.radius, object.length))) && ft_dist(object.pos, result[1]) <= hypot(object.radius, object.length)))))
		return (result[1]);
	if((root[0] > 0 && (ft_dist(origin, result[1]) < PRECISION || isnan(root[1])) && !isnan(root[0])) || ((ft_dist(origin, result[0]) > PRECISION) && root[0] > 0 && (!isnan(root[0])  && ((root[1] < 0 || (ft_dist(origin, result[0]) < ft_dist(origin, result[1]) || ft_dist(object.pos, result[1]) > hypot(object.radius, object.length))) && (ft_dist(object.pos, result[0]) <= hypot(object.radius, object.length))))))
		return (result[0]);
	return ((t_coord){
			.x = NAN,
	});
}

int		ft_square_intersection(t_mrt_list object, t_coord intersection)
{
	t_coord	point[4];
	t_coord	vect1;
	t_coord	vect2;

	if (object.vect.x == 0 && object.vect.y == 0)
		vect1 = (t_coord){
			.x = 1
		};
	else if (object.vect.z == 0)
		vect1 = (t_coord) {
				.z = 1
		};
	else
		vect1 = ft_unit_vect(ft_vector_rotation(object.vect, ft_vector_rotation(
				ft_coord(object.vect.x, object.vect.y, 0), ft_coord(0, 0, 1),
				M_PI_2), M_PI_2));
	vect2 = ft_unit_vect(ft_vector_rotation(vect1, object.vect, M_PI_2));
	vect1.x *= object.length;
	vect1.y *= object.length;
	vect1.z *= object.length;
	vect2.x *= object.length;
	vect2.y *= object.length;
	vect2.z *= object.length;
	point[0] = ft_coord_addition(vect1, vect2);
	point[1] = ft_coord_addition(vect1, ft_vect_calc(vect2, (t_coord){}));
	point[2] = ft_coord_addition(ft_vect_calc(vect1, (t_coord){}), ft_vect_calc(vect2, (t_coord){}));
	point[3] = ft_coord_addition(ft_vect_calc(vect1, (t_coord){}), vect2);
	return(	ft_scalar(object.vect, ft_vect_product(ft_vect_calc(*point, *(point + 1)), ft_vect_calc(*point, intersection))) < 0 &&
			ft_scalar(object.vect, ft_vect_product(ft_vect_calc(*(point + 1), *(point + 2)), ft_vect_calc(*(point + 1), intersection))) < 0 &&
			ft_scalar(object.vect, ft_vect_product(ft_vect_calc(*(point + 2), *(point + 3)), ft_vect_calc(*(point + 2), intersection))) < 0 &&
			ft_scalar(object.vect, ft_vect_product(ft_vect_calc(*(point + 3), *point), ft_vect_calc(*(point + 3), intersection))) < 0);
}

t_coord		ft_plane_intersection(t_coord vect, t_coord origin, t_mrt_list object)
{
	double 	t;
	t_coord	result;
//		ax + by +cz +d = 0
//		object.vect.x * (origin.x + t * vect.x)  + object.vect.y *  (origin.y + t * vect.y) + object.vect.z  * (origin.z + t * vect.z)
//		d  =  object.vect.x * object.pos.x + object.vect.y * object.pos.y + object.vect.z * object.pos.z
//		vect.x * object.vect.x * t + object.vect.x * origin.x + vect.y * object.vect.y * t + object.vect.y * origin.y + vect.z * object.vect.z * t + object.vect.z * origin.z
//		t * (vect.x * object.vect.x + vect.y * object.vect.y + vect.z * object.vect.z) + object.vect.x * origin.x + object.vect.y * origin.y + object.vect.z * origin.z  -  (object.vect.x * object.pos.x + object.vect.y * object.pos.y + object.vect.z * object.pos.z)   = 0
//		t = -(object.vect.x * origin.x + object.vect.y * origin.y + object.vect.z * origin.z  -  (object.vect.x * object.pos.x + object.vect.y * object.pos.y + object.vect.z * object.pos.z)) / (vect.x * object.vect.x + vect.y * object.vect.y + vect.z * object.vect.z)
	if (object.id ==TRIANGLE)
		object.vect = ft_unit_vect(ft_vect_product(ft_vect_calc(*object.polygon, *(object.polygon + 1)), ft_vect_calc(*object.polygon, *(object.polygon + 2))));
	t = -((object.vect.x * (origin.x - object.pos.x) + object.vect.y * (origin.y - object.pos.y) + object.vect.z * (origin.z - object.pos.z)) / (vect.x * object.vect.x + vect.y * object.vect.y + vect.z * object.vect.z));
	result.x = origin.x + t * vect.x;
	result.y = origin.y + t * vect.y;
	result.z = origin.z + t * vect.z;
	if (t > 0 && ((object.id == PLANE) ||
			(object.id == DISK && ft_dist(object.pos, result) <= object.radius) ||
		(object.id == TRIANGLE &&
		ft_scalar(object.vect, ft_vect_product(ft_vect_calc(*object.polygon, *(object.polygon + 1)), ft_vect_calc(*object.polygon, result))) > PRECISION &&
		ft_scalar(object.vect, ft_vect_product(ft_vect_calc(*(object.polygon + 1), *(object.polygon + 2)), ft_vect_calc(*(object.polygon + 1), result))) > PRECISION &&
		ft_scalar(object.vect, ft_vect_product(ft_vect_calc(*(object.polygon + 2), *object.polygon), ft_vect_calc(*(object.polygon + 2), result))) > PRECISION) ||
		(object.id == SQUARE && ft_square_intersection(object, result))))
		return (result);
	return ((t_coord){
		.x = NAN,
	});
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
	else if (object.id == SQUARE || object.id == PLANE || object.id == DISK || object.id == TRIANGLE)
		result = ft_plane_intersection(vect, origin, object);
	if (ft_dist(origin, result) < 0.000001)
		result = (t_coord){
				.x = NAN,
				.y = NAN,
				.z = NAN
		};
	return(result);
}
