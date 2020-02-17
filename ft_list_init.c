/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 14:39:55 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 21:54:43 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** error protection OK :D
*/

int		ft_isspace(char c)
{
	return (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == ' ');
}

int		ft_strstart(char *s1, char *s2)
{
	return (*s1 == *s2 && *(s1 + 1) == *(s2 + 1));
}

int		ft_is_in_charset(char *charset, char c)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

void	ft_list_init2(int fd, t_all_info *all_info,
		char **line, int old)
{
	int	ret;

	while ((ret = get_next_line(fd, line)) == 1 || old == 1)
	{
		if (ret == -1)
			ft_quit(*all_info, ERR_SYS);
		old = ret;
		if (**line && ft_is_in_charset("RAclafsptd", **line))
		{
			if (((**line == 'R' || **line == 'A' || **line == 'f' ||
			**line == 'c') && ft_isspace(*(*line + 1))) ||
			ft_strstart(*line, "aa") || ft_strstart(*line, "st") ||
			ft_strstart(*line, "sk"))
				ret = ft_scene_init(all_info, *line);
			else if (**line == 'l' && ft_isspace(*(*line + 1)))
				ret = ft_lights_init(all_info->lights, *line);
			else if (ft_strstart(*line, "sp") || ft_strstart(*line, "pl")
			|| ft_strstart(*line, "sq") || ft_strstart(*line, "cy") ||
			ft_strstart(*line, "tr") || ft_strstart(*line, "di"))
				ret = ft_obj_init(*all_info, *line);
		}
		free(*line);
		if (ret == -1)
			ft_quit(*all_info, FILE_ERR);
	}
}

void	ft_list_init(int fd, t_all_info *all_info)
{
	char		**line;
	t_mrt_list	*tmp;

	if (!(line = malloc(sizeof(char *))))
		ft_quit(*all_info, ERR_SYS);
	*all_info->lights = (t_mrt_list){.id = 0};
	*all_info->cameras = (t_mrt_list){.id = 0};
	*all_info->objects = (t_mrt_list){.id = 0};
	all_info->scene_info.skysphere = (t_image){.dim.i = 0};
	all_info->scene_info = (t_info){.light = -1};
	all_info->scene_info.fi = (t_color){255, 255, 255};
	ft_list_init2(fd, all_info, line, 2);
	if (line)
		free(*line);
	tmp = all_info->lights;
	all_info->lights = all_info->lights->next;
	free(tmp);
	tmp = all_info->objects;
	all_info->objects = all_info->objects->next;
	free(tmp);
	tmp = all_info->cameras;
	all_info->cameras = all_info->cameras->next;
	free(tmp);
	free(line);
}
