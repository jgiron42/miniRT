/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   somevectormanipulation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:20:34 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/13 18:26:56 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**error protection OK :D
*/

t_coord		ft_vector_rotation(t_coord vect, t_coord axe, double angle)
{
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	return ((t_coord){
	vect.x * (axe.x * axe.x * (1 - c) + c) +
			vect.y * (axe.x * axe.y * (1 - c) - axe.z * s) +
			vect.z * (axe.x * axe.z * (1 - c) + axe.y * s),
	vect.x * (axe.x * axe.y * (1 - c) + axe.z * s) +
			vect.y * (axe.y * axe.y * (1 - c) + c) +
			vect.z * (axe.y * axe.z * (1 - c) - axe.x * s),
	vect.x * (axe.x * axe.z * (1 - c) - axe.y * s) +
			vect.y * (axe.y * axe.z * (1 - c) + axe.x * s) +
			vect.z * (axe.z * axe.z * (1 - c) + c)
	});
}

t_coord		ft_vect_calc(t_coord a, t_coord b)
{
	return ((t_coord){
		b.x - a.x,
		b.y - a.y,
		b.z - a.z
	});
}

double		ft_dist(t_coord a, t_coord b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) +
	(b.z - a.z) * (b.z - a.z)));
}

double		ft_scalar(t_coord a, t_coord b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_coord		ft_unit_vect(t_coord vect)
{
	double length;

	length = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
	return ((t_coord){
		.x = vect.x / length,
		.y = vect.y / length,
		.z = vect.z / length
	});
}
