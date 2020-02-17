/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:39:03 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 21:12:04 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** error protection OK :D
*/

static void	ft_obj_tr(t_all_info all_info, t_mrt_list *result, char **line)
{
	int	i;

	i = -1;
	if (!(result->polygon = malloc(3 * sizeof(t_coord))))
		ft_quit(all_info, ERR_SYS);
	while (++i < 3)
		if (ft_atocoord(&result->polygon[i], line) == -1)
			ft_quit(all_info, FILE_ERR);
	result->pos = (t_coord){
		(result->polygon->x + result->polygon[1].x + result->polygon[2].x) / 3,
		(result->polygon->y + result->polygon[1].y + result->polygon[2].y) / 3,
		(result->polygon->z + result->polygon[1].z + result->polygon[2].z) / 3
	};
}

char		ft_find_id(char *line)
{
	if (ft_strstart(line, "tr"))
		return (TRIANGLE);
	if (ft_strstart(line, "pl"))
		return (PLANE);
	if (ft_strstart(line, "sp"))
		return (SPHERE);
	if (ft_strstart(line, "sq"))
		return (SQUARE);
	if (ft_strstart(line, "cy"))
		return (CYLINDER);
	if (ft_strstart(line, "di"))
		return (DISK);
	return (-1);
}

int			ft_obj_init(t_all_info all_info, char *line)
{
	t_mrt_list	*res;

	while (all_info.objects->next)
		all_info.objects = all_info.objects->next;
	if (!(res = malloc(sizeof(t_mrt_list))))
		ft_quit(all_info, ERR_SYS);
	all_info.objects->next = res;
	*res = (t_mrt_list){ft_find_id(line),
						{0, 0, 0}, {0, 0, 0}, 0, {0, 0, 0}, 0, 0, 0, 0};
	line += 2;
	if (res->id == TRIANGLE)
		ft_obj_tr(all_info, res, &line);
	else
	{
		if (-1 == ft_atocoord(&(res->pos), &line))
			ft_quit(all_info, FILE_ERR);
		if (res->id != SPHERE)
			if (-1 == ft_atocoord(&(res->vect), &line))
				ft_quit(all_info, FILE_ERR);
		if (res->id == SPHERE || res->id == CYLINDER || res->id == DISK)
			res->radius = ft_atof(&line) / 2;
		if (res->id == SQUARE || res->id == CYLINDER)
			res->length = ft_atof(&line) / 2;
	}
	return (ft_atocolor(&(res->color), &line));
}
