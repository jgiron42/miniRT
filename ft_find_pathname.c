/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_pathname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 21:02:50 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 21:09:57 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_find_pathname2(char *const *argv, t_all_info *all_info, char *tmp,
					char *result)
{
	if (argv[3][ft_strlen(argv[3]) - 1] == '/')
	{
		tmp = ft_find_file_name(argv[1]);
		if (!(result = ft_strjoin(argv[3], tmp)))
			ft_quit((*all_info), ERR_SYS);
		free(tmp);
	}
	else
	{
		if (!(result = ft_strdup(argv[3])))
			ft_quit((*all_info), ERR_SYS);
		if (ft_strnstr(result, ".bmp", ft_strlen(result)))
			*ft_strnstr(result, ".bmp", ft_strlen(result)) = 0;
	}
	return (result);
}

char	*ft_find_pathname(int argc, char **argv, int n, t_all_info all_info)
{
	char	*tmp;
	char	*tmp2;
	char	*result;

	tmp2 = NULL;
	tmp = NULL;
	result = NULL;
	if (argc == 3)
	{
		if (!(result = ft_find_file_name(argv[1])))
			ft_quit(all_info, ERR_SYS);
	}
	else
		result = ft_find_pathname2(argv, &all_info, tmp, result);
	if (!(tmp = n == 0 ? ft_strdup("") : ft_itoa(n)) ||
		!(tmp2 = ft_strjoin(result, tmp)))
		ft_quit(all_info, ERR_SYS);
	free(tmp);
	free(result);
	result = ft_strjoin(tmp2, ".bmp");
	if (tmp2)
		free(tmp2);
	return (result);
}
