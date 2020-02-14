/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 15:48:09 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/14 15:25:56 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//error protection OK :D

static int ft_r_init(t_info *scene_info, char *line)
{
	line++;
	if (scene_info->dim.i != 0)
		return (-1);
	scene_info->dim.i = ft_atoi(line);
	while(*line != 0 && ft_isspace(*line))
		line++;
	while((*line >= 48) && (*line < 58))
		line++;
	if (*line == 0)
		return (-1);
	scene_info->dim.j = ft_atoi(line);
	if (scene_info->dim.i < 1 || scene_info->dim.j < 1)
		return (-1);
	scene_info->dim.i = scene_info->dim.i > SCREEN_WIDTH ?
								 SCREEN_WIDTH : scene_info->dim.i;
	scene_info->dim.j = scene_info->dim.j > SCREEN_HEIGTH ?
								 SCREEN_HEIGTH : scene_info->dim.j;
	return(0);
}



static int	ft_a_init(t_info *scene_info, char *line)
{
	if (*line == 'A' && scene_info->light == -1)
	{
		line++;
		scene_info->light = ft_atof(&line);
		while ((*line >= 48) && (*line < 58))
			line++;
		while (*line != 0 && ft_isspace(*line))
			line++;
		return (ft_atocolor(&(scene_info->color), &line));
	}
	else if (ft_strstart(line, "aa"))
	{
		line += 2;
		scene_info->anti_aliasing = ft_atoi(line);
		return (scene_info->anti_aliasing < 0 ||
		(int)sqrt(scene_info->anti_aliasing) % 2 == 1 ? 1 : 0);
	}
	else if (*line == 'f')
	{
		line++;
		while (*line != 0 && ft_isspace(*line))
			line++;
		if ((*line >= 48) && (*line < 58))
			return (ft_atocolor(&scene_info->fi, &(line)));
	}
	else if (ft_strstart(line, "st"))
	{
		line += 2;
		scene_info->stereo = ft_atof(&line);
		scene_info->stereo_depth = ft_atof(&line);
		return (0);
	}
	return (-1);
}

static int	ft_c_init(t_all_info *all_info, char *line)
{
	t_mrt_list	*result;
	t_mrt_list	*tmp;

	tmp = all_info->cameras;
	while (tmp->next)
		tmp = tmp->next;
	line++;
	if (!(result = malloc(sizeof(t_mrt_list))))
		ft_quit(*all_info, -1);
	tmp->next = result;
	*result = (t_mrt_list){};
	if (-1 == ft_atocoord(&(result->pos), &line))
		return (-1);
	if (-1 == ft_atocoord(&(result->vect), &line))
		return (-1);
	result->vect = ft_unit_vect(result->vect);
	result->length = (M_PI * (double)ft_atoi(line)) / 180;
	return (0);
}

int		ft_scene_init(t_all_info *all_info, char *line)
{
	if (*line == 'R')
		return (ft_r_init(&all_info->scene_info, line));
	else if (*line == 'A' || ft_strstart(line, "aa")|| ft_strstart(line, "st") || *line == 'f' )
		return (ft_a_init(&all_info->scene_info, line));
	else if (*line == 'c')
		return (ft_c_init(all_info, line));
	else if (ft_strstart(line, "sk"))
	{
		line += 2;
		all_info->scene_info.skysphere.luminosity = ft_atof(&line);
		while (ft_isspace(*line))
			line++;
		if (ft_strnstr(line, ".xpm", ft_strlen(line)))
			all_info->scene_info.skysphere.img_ptr = mlx_xpm_file_to_image(all_info->mlx_ptr, line, &all_info->scene_info.skysphere.dim.i, &all_info->scene_info.skysphere.dim.j);
		else if (ft_strnstr(line, ".png", ft_strlen(line)))
			all_info->scene_info.skysphere.img_ptr = mlx_png_file_to_image(all_info->mlx_ptr, line, &all_info->scene_info.skysphere.dim.i, &all_info->scene_info.skysphere.dim.j);
		if (all_info->scene_info.skysphere.img_ptr)
			return (0);
	}
	return (-1);
}
