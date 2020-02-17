/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:26:42 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 18:27:51 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		ft_polynom_2(double a, double b, double c, int root)
{
	double	delta;

	delta = b * b - 4 * a * c;
	if (((root == 2 && delta == 0) || (root == 1 && delta >= 0)) && a != 0)
		return ((-b - sqrt(delta)) / (2 * a));
	else if (root == 2 && delta > 0 && a != 0)
		return ((-b + sqrt(delta)) / (2 * a));
	return (NAN);
}

double		ft_sphere_intersection2(t_coord *vect, t_coord *origin,
		t_mrt_list *object, double *root1)
{
	*root1 = ft_polynom_2((vect->x * vect->x + vect->y * vect->y +
vect->z * vect->z), 2 * (vect->x * (origin->x - object->pos.x) +
vect->y * (origin->y - object->pos.y) + vect->z * (origin->z -
object->pos.z)), (origin->x - object->pos.x) * (origin->x -
object->pos.x) + (origin->y - object->pos.y) * (origin->y -
object->pos.y) + (origin->z - object->pos.z) * (origin->z -
object->pos.z) - object->radius * object->radius, 1);
	return (ft_polynom_2(((*vect).x * (*vect).x + (*vect).y * (*vect).y + (
*vect).z * (*vect).z), 2 * ((*vect).x * ((*origin).x - (*object).pos.x) + (
*vect).y * ((*origin).y - (*object).pos.y) + (*vect).z * ((*origin).z -
(*object).pos.z)), ((*origin).x - (*object).pos.x) * ((*origin).x -
(*object).pos.x) + ((*origin).y - (*object).pos.y) * ((*origin).y -
(*object).pos.y) + ((*origin).z - (*object).pos.z) * ((*origin).z -
(*object).pos.z) - (*object).radius * (*object).radius, 2));
}

t_coord		ft_sphere_intersection(t_coord vect, t_coord origin,
		t_mrt_list object)
{
	double	root1;
	double	root2;
	t_coord	result1;
	t_coord	result2;

	root2 = ft_sphere_intersection2(&vect, &origin, &object, &root1);
	result1.x = origin.x + root1 * vect.x;
	result1.y = origin.y + root1 * vect.y;
	result1.z = origin.z + root1 * vect.z;
	result2.x = origin.x + root2 * vect.x;
	result2.y = origin.y + root2 * vect.y;
	result2.z = origin.z + root2 * vect.z;
	if ((((isnan(root1) || ft_dist(origin, result1) < PRECISION || root1 <
PRECISION) && !isnan(root2)) || (!isnan(root2) && ft_dist(origin, result2) <
ft_dist(origin, result1))) && root2 > PRECISION && ft_dist(origin, result2) >
PRECISION)
		return (result2);
	if ((((isnan(root2) || ft_dist(origin, result2) < PRECISION || root2 <
PRECISION) && !isnan(root1)) || (!isnan(root1) && ft_dist(origin, result1) <
ft_dist(origin, result2))) && root1 > PRECISION && ft_dist(origin, result1) >
PRECISION)
		return (result1);
	return ((t_coord){NAN, NAN, NAN});
}

void		ft_cylinder_intersection2(t_coord *v, t_coord *origin,
			t_mrt_list *o, t_cylinder *result)
{
	int	i;

	i = -1;
	while (++i <= 1)
	{
		result[i].root = ft_polynom_2(v->x * v->x + v->y * v->y + v->z *
v->z - (((o->vect.x * v->x + o->vect.y * v->y + o->vect.z * v->z) * (o->vect.x *
v->x + o->vect.y * v->y + o->vect.z * v->z)) / (o->vect.x * o->vect.x +
o->vect.y * o->vect.y + o->vect.z * o->vect.z)), 2 * ((origin->x - o->pos.x
) * v->x + (origin->y - o->pos.y) * v->y + (origin->z - o->pos.z) * v->z) -
((2 * (o->vect.x * (origin->x - o->pos.x) + o->vect.y * (origin->y - o->pos.y) +
o->vect.z * (origin->z - o->pos.z)) * (o->vect.x * v->x + o->vect.y * v->y +
o->vect.z * v->z)) / (o->vect.x * o->vect.x + o->vect.y * o->vect.y +
o->vect.z * o->vect.z)), (origin->x - o->pos.x) * (origin->x - o->pos.x) +
(origin->y - o->pos.y) * (origin->y - o->pos.y) + (origin->z - o->pos.z) *
(origin->z - o->pos.z) - (((o->vect.x * (origin->x - o->pos.x) + o->vect.y *
(origin->y - o->pos.y) + o->vect.z * (origin->z - o->pos.z)) * (o->vect.x *
(origin->x - o->pos.x) + o->vect.y * (origin->y - o->pos.y) + o->vect.z *
(origin->z - o->pos.z))) / (o->vect.x * o->vect.x + o->vect.y * o->vect.y +
o->vect.z * o->vect.z)) - o->radius * o->radius, i + 1);
		result[i].result.x = (*origin).x + result[i].root * (*v).x;
		result[i].result.y = (*origin).y + result[i].root * (*v).y;
		result[i].result.z = (*origin).z + result[i].root * (*v).z;
	}
}

t_coord		ft_cylinder_intersection(t_coord vect, t_coord origin,
										t_mrt_list object)
{
	t_cylinder result[2];

	ft_cylinder_intersection2(&vect, &origin, &object, result);
	if ((result[1].root > 0 && (ft_dist(origin, result[0].result) < PRECISION ||
isnan(result[0].root)) && !isnan(result[1].root)) || ((ft_dist(origin,
result[1].result) > PRECISION) && result[1].root > 0 && (!isnan(result[1].root)
	&& ((result[0].root < 0 || (ft_dist(origin, result[1].result) < ft_dist(
origin, result[0].result) || ft_dist(object.pos, result[0].result) > hypot(
object.radius, object.length))) && ft_dist(object.pos, result[1].result) <=
hypot(object.radius, object.length)))))
		return (result[1].result);
	if ((result[0].root > 0 && (ft_dist(origin, result[1].result) < PRECISION ||
isnan(result[1].root)) && !isnan(result[0].root)) || ((ft_dist(origin,
result[0].result) > PRECISION) && result[0].root > 0 && (!isnan(result[0].root)
	&& ((result[1].root < 0 || (ft_dist(origin, result[0].result) < ft_dist(
origin, result[1].result) || ft_dist(object.pos, result[1].result) > hypot(
object.radius, object.length))) && (ft_dist(object.pos, result[0].result) <=
hypot(object.radius, object.length))))))
		return (result[0].result);
	return ((t_coord){NAN, NAN, NAN});
}
