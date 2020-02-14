/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_atowhatever.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 17:19:22 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/13 19:13:40 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**error protection OK :D
*/

int			ft_atocoord(t_coord *dst, char **line)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (i == 0)
			dst->x = ft_atof(line);
		else if (i == 1)
			dst->y = ft_atof(line);
		else if (i == 2)
			dst->z = ft_atof(line);
		while (ft_isspace(**line) && i != 2)
			(*line)++;
		while (((**line >= 48) && (**line < 58)) || **line == '-')
			(*line)++;
		if (i != 2 && (**line != ',' || !(((*(*line + 1) >= 48) &&
		(*(*line + 1) < 58)) || (*(*line + 1) == '-'))))
			return (-1);
		(*line)++;
	}
	return (0);
}

int			ft_atocolor(t_color *dst, char **line)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (i == 0)
			dst->r = (int)ft_atof(line);
		else if (i == 1)
			dst->g = (int)ft_atof(line);
		else if (i == 2)
			dst->b = (int)ft_atof(line);
		while (ft_isspace(**line))
			(*line)++;
		while ((**line >= 48) && (**line < 58))
			(*line)++;
		if (i != 2 &&
			(**line != ',' || !((*(*line + 1) >= 48) && (*(*line + 1) < 58))))
			return (-1);
		(*line)++;
	}
	return (0);
}

double		ft_atof(char **str)
{
	double	a;
	double	b;
	int		i;
	int		sign;

	i = 0;
	if (!str || !*str)
		return (0);
	while (ft_isspace(**str))
		(*str)++;
	sign = **str == 45 ? -1 : 1;
	a = fabs((double)ft_atoi(*str));
	while (((**str >= 48) && (**str < 58)) || **str == 45)
		(*str)++;
	if (**str != '.')
		return (a * sign);
	(*str)++;
	while ((*str)[i] == '0')
		i++;
	b = ft_atoi(*str);
	while (((**str >= 48) && (**str < 58)))
		(*str)++;
	if (b == 0)
		return ((double)a);
	b = (b / pow(10, floor(log10(b) + 1 + i)));
	return ((a + b) * sign);
}
