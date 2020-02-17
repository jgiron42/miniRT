/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_vector_manipulation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:26:03 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/13 18:26:20 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord		ft_vect_product(t_coord a, t_coord b)
{
	return ((t_coord){
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x,
	});
}

t_coord		ft_coord(double x, double y, double z)
{
	return ((t_coord){
			.x = x,
			.y = y,
			.z = z
	});
}

t_coord		ft_coord_addition(t_coord a, t_coord b)
{
	return ((t_coord){
			a.x + b.x,
			a.y + b.y,
			a.z + b.z
	});
}

t_color		ft_color_addition(t_color a, t_color b)
{
	return ((t_color){
			a.r + b.r,
			a.g + b.g,
			a.b + b.b
	});
}
