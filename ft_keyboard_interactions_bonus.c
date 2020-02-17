/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard_interactions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:11:59 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 18:43:23 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** error protection OK :D
*/

static void	ft_triangle_movement(int keycode, t_all_info all_info,
		t_mrt_list *triangle)
{
	int		i;
	t_coord	tmp;

	i = -1;
	while (++i < 3)
	{
		if (keycode >= 123 && keycode <= 126)
		{
			triangle->pos = (t_coord){
				(triangle->polygon->x + triangle->polygon[1].x +
				triangle->polygon[2].x) / 3,
				(triangle->polygon->y + triangle->polygon[1].y +
				triangle->polygon[2].y) / 3,
				(triangle->polygon->z + triangle->polygon[1].z +
				triangle->polygon[2].z) / 3
			};
			tmp = ft_vect_calc(triangle->pos, triangle->polygon[i]);
			ft_rotation(keycode, &tmp);
			triangle->polygon[i] = ft_coord_addition(triangle->pos, tmp);
		}
		ft_translation(keycode, triangle->polygon + i,
				all_info.cameras->vect);
	}
}

void		ft_get_object_str2(t_mrt_list *first_object, const
		t_mrt_list *current_object, int *total, char **object_name)
{
	while (first_object->next)
	{
		if (first_object->id == current_object->id)
			(*total)++;
		first_object = first_object->next;
	}
	if (current_object->id == PLANE)
		(*object_name) = ft_strdup("Plane ");
	else if (current_object->id == TRIANGLE)
		(*object_name) = ft_strdup("Triangle ");
	else if (current_object->id == SQUARE)
		(*object_name) = ft_strdup("Square ");
	else if (current_object->id == SPHERE)
		(*object_name) = ft_strdup("Sphere ");
	else if (current_object->id == CYLINDER)
		(*object_name) = ft_strdup("Cylinder ");
	else if (current_object->id == DISK)
		(*object_name) = ft_strdup("Disk ");
	else
		(*object_name) = ft_strdup("");
}

char		*ft_get_object_str(t_all_info all_info, t_mrt_list *first_object,
		t_mrt_list *current_object)
{
	int		n;
	int		total;
	char	*object_name;
	char	*result;
	char	*number;

	n = 1;
	if (all_info.scene_info.mode % 2 == 0)
		return (ft_strdup(""));
	while (first_object != current_object && first_object->next)
	{
		if (first_object->id == current_object->id)
			n++;
		first_object = first_object->next;
	}
	total = n;
	ft_get_object_str2(first_object, current_object, &total, &object_name);
	number = total > n ? ft_itoa(n) : ft_strdup("");
	if (!object_name || !number)
		ft_quit(all_info, ERR_SYS);
	result = ft_strjoin(object_name, number);
	free(object_name);
	free(number);
	return (result);
}

t_mrt_list	*ft_keyboard_interaction2(int keycode, t_all_info *all_info,
		t_mrt_list *first_object, t_mrt_list *current_object)
{
	if (keycode == 53)
		ft_quit(*all_info, 0);
	else if (keycode == 12 && all_info->scene_info.dim.i > 100 &&
		all_info->scene_info.dim.j > 100)
		all_info->scene_info.zoom++;
	else if (keycode == 14)
		all_info->scene_info.mode++;
	else if (keycode == 78 && all_info->cameras->length < M_PI - M_PI / 36)
		all_info->cameras->length += M_PI / 36;
	else if (keycode == 69 && all_info->cameras->length > M_PI / 36)
		all_info->cameras->length -= M_PI / 36;
	else if (keycode == 48)
		current_object = current_object->next ? current_object->next
				: first_object;
	else if (all_info->scene_info.mode % 2 == 1 &&
	current_object->id == TRIANGLE)
		ft_triangle_movement(keycode, *all_info, current_object);
	if (keycode >= 123 && keycode <= 126)
		ft_rotation(keycode, all_info->scene_info.mode % 2 == 1 ?
		&current_object->vect : &all_info->cameras->vect);
	else
		ft_translation(keycode, all_info->scene_info.mode % 2 == 1 ?
	&current_object->pos : &all_info->cameras->pos, all_info->cameras->vect);
	return (current_object);
}

int			ft_keyboard_interaction(int keycode, t_all_info *all_info)
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
	if (keycode == 49)
		all_info->cameras = all_info->cameras->next ? all_info->cameras->next
													: first_cam;
	current_object = ft_keyboard_interaction2(keycode, all_info, first_object,
			current_object);
	ft_put_scene(*all_info, ft_get_object_str(*all_info, first_object,
			current_object), NULL);
	return (0);
}
