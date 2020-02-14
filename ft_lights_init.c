/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lights_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:22:03 by jgiron            #+#    #+#             */
/*   Updated: 2019/12/15 22:01:14 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//error protection OK :D

int		ft_lights_init(t_mrt_list *lights, char *line)
{
	t_mrt_list	*result;

	line++;
	while (lights->next)
		lights = lights->next;
	if (!(result = malloc(sizeof(t_mrt_list))))
		return (-1);
	*result = (t_mrt_list){};
	lights->next = result;
	if (-1 == ft_atocoord(&(result->pos), &line))
		return (-1);
	result->light = ft_atof(&line);
	return (ft_atocolor(&(result->color), &line));
}
