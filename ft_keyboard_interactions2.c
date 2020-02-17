/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard_interactions2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:01:45 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 22:27:24 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_rotation(int keycode, t_coord *vect)
{
	if (keycode == 125)
		*vect = ft_unit_vect(ft_vector_rotation(*vect, ft_vector_rotation(
				ft_unit_vect((t_coord){vect->x, vect->y, 0}),
		ft_coord(0, 0, 1), M_PI_2), M_PI / ROTATION_SPEED));
	if (keycode == 126)
		*vect = ft_unit_vect(ft_vector_rotation(*vect, ft_vector_rotation(
				ft_unit_vect((t_coord){vect->x, vect->y, 0}),
		ft_coord(0, 0, 1), M_PI_2), -M_PI / ROTATION_SPEED));
	if (keycode == 123)
		*vect = ft_unit_vect(ft_vector_rotation(*vect, ft_coord(0, 0, 1),
										-M_PI / ROTATION_SPEED));
	if (keycode == 124)
		*vect = ft_unit_vect(ft_vector_rotation(*vect, ft_coord(0, 0, 1),
						M_PI / ROTATION_SPEED));
}

void	ft_translation(int keycode, t_coord *pos, t_coord vect)
{
	if (keycode == 13)
		*pos = ft_coord_addition(*pos, ft_unit_vect(vect));
	else if (keycode == 1)
		*pos = ft_vect_calc(ft_unit_vect(vect), *pos);
	else if (keycode == 0)
		*pos = ft_coord_addition(*pos, ft_unit_vect(ft_vector_rotation(
	ft_unit_vect(ft_coord(vect.x, vect.y, 0)), ft_coord(0, 0, 1), -M_PI_2)));
	else if (keycode == 2)
		*pos = ft_coord_addition(*pos, ft_unit_vect(ft_vector_rotation(
	ft_unit_vect(ft_coord(vect.x, vect.y, 0)), ft_coord(0, 0, 1), M_PI_2)));
	else if (keycode == 256)
		*pos = ft_coord_addition(*pos, ft_unit_vect(ft_vector_rotation(vect,
ft_vector_rotation(ft_unit_vect((t_coord){vect.x, vect.y, 0}),
		ft_coord(0, 0, 1), M_PI_2), M_PI_2)));
	else if (keycode == 257)
		*pos = ft_coord_addition(*pos, ft_unit_vect(ft_vector_rotation(
vect, ft_vector_rotation(ft_unit_vect((t_coord){vect.x, vect.y,
	0}), ft_coord(0, 0, 1), M_PI_2), 3 * M_PI_2)));
}
