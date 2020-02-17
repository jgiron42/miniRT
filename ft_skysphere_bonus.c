/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skysphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:34:00 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 18:53:05 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**error protection OK :D
*/

t_color	ft_skysphere(t_all_info all_info, t_coord vect)
{
	t_pix	pixel;
	char	*address;
	t_coord	vect_hor;

	if ((vect.x == 0 && vect.y == 0) || !all_info.scene_info.skysphere.img_ptr)
		return ((t_color){0, 0, 0});
	vect_hor = ft_unit_vect((t_coord){vect.x, vect.y, 0});
	pixel.i = (int)(((M_PI + ((asin(vect.x) / fabs(asin(vect.x))) *
acos(vect_hor.y))) / (2 * M_PI)) * (double)all_info.scene_info.skysphere.dim.i);
	pixel.j = (int)((acos(vect.z) / M_PI) *
(double)all_info.scene_info.skysphere.dim.j);
	address = ft_get_img_address(all_info.scene_info.skysphere.img_ptr,
			24, all_info.scene_info.skysphere.dim.i, 1);
	return ((t_color){
			(int)((double)*(unsigned char *)(address + 4 * pixel.j *
all_info.scene_info.skysphere.dim.i + pixel.i * 4 + 2) * ((double)
all_info.scene_info.color.r / 255) * all_info.scene_info.skysphere.luminosity),
(int)((double)*(unsigned char *)(address + 4 * pixel.j
	* all_info.scene_info.skysphere.dim.i + pixel.i * 4 + 1) * ((double)
all_info.scene_info.color.r / 255) * all_info.scene_info.skysphere.luminosity),
(int)((double)*(unsigned char *)(address + 4 * pixel.j *
all_info.scene_info.skysphere.dim.i + pixel.i * 4) * ((double)
all_info.scene_info.color.r / 255) * all_info.scene_info.skysphere.luminosity)
	});
}
