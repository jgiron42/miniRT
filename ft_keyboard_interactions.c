/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard_interactions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:11:59 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/11 18:57:43 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//error protection OK :D

static void ft_rotation(int keycode, t_coord *vect)
{
	if (keycode == 126)
		*vect = ft_unit_vect(ft_vector_rotation(*vect, vect->z == 1 ? ft_coord(0,1,0) : ft_vector_rotation(ft_coord(vect->x, vect->y, 0), ft_coord(0,0,1), - M_PI_2), M_PI / ROTATION_SPEED));
	if (keycode == 125)
		*vect = ft_unit_vect(ft_vector_rotation(*vect, vect->z == 1 ? ft_coord(0,1,0) : ft_vector_rotation(ft_coord(vect->x, vect->y, 0), ft_coord(0,0,1), - M_PI_2), -M_PI / ROTATION_SPEED));
	if (keycode == 123)
		*vect = ft_unit_vect(ft_vector_rotation(*vect, vect->z == 1 ? ft_coord(1,0,0) : ft_coord(0,0,1), -M_PI / ROTATION_SPEED));
	if (keycode == 124)
		*vect = ft_unit_vect(ft_vector_rotation(*vect, vect->z == 1 ? ft_coord(1,0,0) : ft_coord(0,0,1), M_PI / ROTATION_SPEED));
}

static void	ft_translation(int keycode, t_coord *pos, t_coord vect)
{
	if (keycode == 13)
		*pos = ft_coord_addition(*pos, ft_unit_vect(vect));
	else if (keycode == 1)
		*pos = ft_vect_calc(ft_unit_vect(vect), *pos);
	else if (keycode == 0)
		*pos = ft_coord_addition(*pos, ft_unit_vect(ft_vector_rotation(ft_coord(vect.x, vect.y, 0), ft_coord(0,0,1), -M_PI_2)));
	else if (keycode == 2)
		*pos = ft_coord_addition(*pos, ft_unit_vect(ft_vector_rotation(ft_coord(vect.x, vect.y, 0), ft_coord(0,0,1), M_PI_2)));
	else if (keycode == 257)
		*pos = ft_coord_addition(*pos, ft_unit_vect(ft_vector_rotation(vect, ft_vector_rotation(ft_coord(vect.x, vect.y, 0), ft_coord(0,0,1), - M_PI_2), M_PI_2)));
	else if (keycode == 256)
		*pos = ft_vect_calc(ft_unit_vect(ft_vector_rotation(vect, ft_vector_rotation(ft_coord(vect.x, vect.y, 0), ft_coord(0,0,1), - M_PI_2), M_PI_2)), *pos);

}

char 	*ft_get_object_str(t_all_info all_info, t_mrt_list *first_object, t_mrt_list *current_object)
{
	int n;
	int total;
	char *object_name;
	char *result;
	char *number;

	n = 1;
	if (all_info.scene_info.mode % 2 == 0)
		return(ft_strdup(""));
	while (first_object != current_object && first_object->next)
	{
		if (first_object->id == current_object->id)
			n++;
		first_object = first_object->next;
	}
	total = n;
	while (first_object->next)
	{
		if (first_object->id == current_object->id)
			total++;
		first_object = first_object->next;
	}
	if (current_object->id == PLANE)
		object_name = ft_strdup("Plane ");
	else if (current_object->id == TRIANGLE)
		object_name = ft_strdup("Triangle ");
	else if (current_object->id == SQUARE)
		object_name = ft_strdup("Square ");
	else if (current_object->id == SPHERE)
		object_name = ft_strdup("Sphere ");
	else if (current_object->id == CYLINDER)
		object_name = ft_strdup("Cylinder ");
	else if (current_object->id == DISK)
		object_name = ft_strdup("Disk ");
	else
		object_name = ft_strdup("");
	number = total > n ? ft_itoa(n) : ft_strdup("");
	if (!object_name || !number)
		ft_quit(all_info, ERR_SYS);
	result = ft_strjoin(object_name, number);
	free(object_name);
	free(number);
	return(result);
}

int		ft_keyboard_interaction(int keycode, t_all_info *all_info)
{
	static t_mrt_list *first_cam;
	static t_mrt_list *first_object;
	static t_mrt_list *current_object;

	if (!first_cam)
		first_cam = all_info->cameras;
	if (!first_object)
	{
		first_object = all_info->objects;
		current_object = first_object;
	}
	if (keycode == 53)
		ft_quit(*all_info, 0);
	else if (keycode == 49)
		all_info->cameras = all_info->cameras->next ? all_info->cameras->next :	first_cam;
	else if (keycode >= 123 && keycode <= 126)
		ft_rotation(keycode, all_info->scene_info.mode % 2 == 1 ? &current_object->vect : &all_info->cameras->vect);
	else if (keycode == 12 && all_info->scene_info.dim.i > 100 && all_info->scene_info.dim.j > 100)
		all_info->scene_info.zoom++;
	else if (keycode == 48)
		current_object = current_object->next ? current_object->next : first_object;
	else if (keycode == 14)
		all_info->scene_info.mode++;
	else if (keycode == 78 && all_info->cameras->length < M_PI - M_PI / 36)
		all_info->cameras->length += M_PI / 36;
	else if (keycode == 69 && all_info->cameras->length > M_PI / 36)
		all_info->cameras->length -= M_PI / 36;
	else
		ft_translation(keycode, all_info->scene_info.mode % 2 == 1 ?
	&current_object->pos : &all_info->cameras->pos, all_info->cameras->vect);
	ft_put_scene(*all_info, ft_get_object_str(*all_info, first_object, current_object));
	return (0);
}
