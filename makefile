# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgiron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 16:00:42 by jgiron            #+#    #+#              #
#    Updated: 2020/02/14 16:35:45 by jgiron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

SRCS		=	main.c					\
			ft_put_scene.c				\
			ft_stereo.c					\
			ft_anti_aliasing.c			\
			ft_skysphere.c				\
			ft_list_init.c				\
			ft_luminosity.c				\
			ft_minirt.c					\
			ft_obj_init.c				\
			ft_scene_init.c				\
			ft_lights_init.c			\
			intersections.c				\
			ft_quit.c					\
			somevectormanipulation.c	\
			some_atowhatever.c			\
			get_next_line.c				\
			get_next_line_utils.c		\
			ft_keyboard_interactions.c	\
			ft_zoom.c					\
			ft_save_image.c				\
			more_vector_manipulation.c

OBJS		=	$(SRCS:.c=.o)

CFLAGS		+=	-Wall -Werror -Wextra

FRAMEWORKS	=	-framework OpenGL -framework AppKit

LIBS		=	-lz -Lminilibx -lmlx -Llibft -lft

all		:
			@make $(NAME)

$(NAME)		:	$(OBJS) make_libs
			gcc -o $(NAME) $(LIBS) $(OBJS) $(FRAMEWORKS)

make_libs	:
			@make -C libft
			@make -C minilibx

bonus		:
			@make $(NAME)

clean		:
			rm -f $(OBJS)
			@make -C libft clean
			@make -C minilibx clean

fclean		:	clean
			rm -f $(NAME)
			@make -C libft fclean

re		:	fclean all
