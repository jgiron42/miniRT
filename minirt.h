/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 14:22:02 by jgiron            #+#    #+#             */
/*   Updated: 2020/02/16 18:41:53 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MINIRT_H
# define MINIRT_MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <strings.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"

# ifndef ROTATION_SPEED
#  define ROTATION_SPEED	30
# endif
# ifndef TRANSLATION_SPEED
#  define TRANSLATION_SPEED	1
# endif

# ifndef SCREEN_HEIGTH
#  define SCREEN_HEIGTH 1440
# endif
# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 2560
# endif

# define ERR_SYS		-1
# define MLX_ERR		1
# define FILE_ERR	2
# define ARG_ERR		3

# define PRECISION	0.000001

# ifndef HUD_COLOR
#  define HUD_COLOR	0xf000f0
# endif

# define PLANE		1
# define SPHERE		2
# define TRIANGLE	3
# define SQUARE		4
# define CYLINDER	5
# define DISK		6

typedef struct	s_coord
{
	double	x;
	double	y;
	double	z;
}				t_coord;

typedef struct	s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}				t_color;

typedef struct	s_pix
{
	int i;
	int j;
}				t_pix;

typedef struct	s_image
{
	void	*img_ptr;
	t_pix	dim;
	double	luminosity;
}				t_image;

typedef struct	s_mrt_list
{
	char				id;
	t_coord				pos;
	t_coord				vect;
	double				light;
	t_color				color;
	double				radius;
	double				length;
	t_coord				*polygon;
	struct s_mrt_list	*next;
}				t_mrt_list;

typedef struct	s_info
{
	t_pix	dim;
	double	light;
	t_color	color;
	char	mode;
	char	zoom;
	double	stereo;
	double	stereo_depth;
	int		anti_aliasing;
	t_image	skysphere;
	t_color	fi;
}				t_info;

typedef struct	s_all_info
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_mrt_list	*objects;
	t_mrt_list	*cameras;
	t_mrt_list	*lights;
	t_info		scene_info;
	char		*program_name;
}				t_all_info;

typedef struct	s_cylinder
{
	double	root;
	t_coord	result;
}				t_cylinder;

int				ft_atocoord(t_coord *dst, char **line);
int				ft_atocolor(t_color *dst, char **line);
double			ft_atof(char **str);
int				ft_isspace(char c);
int				ft_strstart(char *s1, char *s2);
void			ft_list_init(int fd, t_all_info *all_info);
int				ft_scene_init(t_all_info *all_info, char *line);
int				ft_lights_init(t_mrt_list *lights, char *line);
int				ft_obj_init(t_all_info all_info, char *line);
t_coord			ft_vect_calc(t_coord a, t_coord b);
t_coord			ft_vector_rotation(t_coord vect, t_coord axe, double angle);
double			ft_dist(t_coord a, t_coord b);
double			ft_scalar(t_coord a, t_coord b);
t_coord			ft_unit_vect(t_coord vect);
double		ft_polynom_2(double a, double b, double c, int root);
t_coord		ft_sphere_intersection(t_coord vect, t_coord origin,
		t_mrt_list object);
t_coord		ft_cylinder_intersection(t_coord vect, t_coord origin,
										t_mrt_list object);
t_coord			ft_intersection(t_coord vect, t_coord origin,
															t_mrt_list object);
t_color			ft_luminosity(t_all_info all_info, t_mrt_list current,
													t_coord original_vector);
t_coord			ft_vect_product(t_coord a, t_coord b);
t_coord			ft_coord(double x, double y, double z);
t_coord			ft_coord_addition(t_coord a, t_coord b);
t_color			ft_color_addition(t_color a, t_color b);
char			*ft_get_img_address(void *img_ptr, int bits_per_pixel,
											int size_line, int endian);
int				ft_keyboard_interaction(int keycode, t_all_info *all_info);
char			*ft_find_file_name(char *path);
void			ft_put_scene(t_all_info all_info, char *object_str, char *arg);
void			ft_zoom(t_all_info all_info, char *img_addr);
void			ft_minirt(t_all_info all_info);
int				ft_stereo(t_all_info all_info, t_pix pixel);
t_color			ft_anti_aliasing(t_all_info all_info, t_pix pixel);
t_color			ft_pixel_calc(t_all_info all_info, t_pix pixel,
														t_mrt_list *objects);
t_color			ft_skysphere(t_all_info all_info, t_coord vect);
void			ft_save_all_image(t_all_info all_info, int argc, char **argv);
char			*ft_find_pathname(int argc, char **argv, int n,
		t_all_info all_info);
void			ft_save_image(t_all_info all_info, int argc, char **argv,
																		int n);
void		ft_rotation(int keycode, t_coord *vect);
void		ft_translation(int keycode, t_coord *pos, t_coord vect);
int			ft_quit(t_all_info all_info, int error);

#endif
