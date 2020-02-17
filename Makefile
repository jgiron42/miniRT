# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgiron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 16:00:42 by jgiron            #+#    #+#              #
#    Updated: 2020/02/17 19:12:51 by jgiron           ###   ########.fr        #
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
			more_vector_manipulation.c  \
			intersections2.c            \
			ft_keyboard_interactions2.c \
			ft_find_pathname.c

SRCS_BONUS		=	main_bonus.c					\
			ft_put_scene_bonus.c				\
			ft_stereo_bonus.c					\
			ft_anti_aliasing_bonus.c			\
			ft_skysphere_bonus.c				\
			ft_list_init_bonus.c				\
			ft_luminosity_bonus.c				\
			ft_minirt_bonus.c					\
			ft_obj_init_bonus.c				\
			ft_scene_init_bonus.c				\
			ft_lights_init_bonus.c			\
			intersections_bonus.c				\
			ft_quit_bonus.c					\
			somevectormanipulation_bonus.c	\
			some_atowhatever_bonus.c			\
			get_next_line_bonus.c				\
			get_next_line_utils_bonus.c		\
			ft_keyboard_interactions_bonus.c	\
			ft_zoom_bonus.c					\
			ft_save_image_bonus.c				\
			more_vector_manipulation_bonus.c  \
			intersections2_bonus.c            \
			ft_keyboard_interactions2_bonus.c \
			ft_find_pathname_bonus.c

OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)

CFLAGS		+=	-Wall -Werror -Wextra

FRAMEWORKS	=	-framework OpenGL -framework AppKit

LIBS		=	-lz -Lminilibx -lmlx -Llibft -lft

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				@make make_libs
				gcc -o $(NAME) $(LIBS) $(OBJS) $(FRAMEWORKS)

bonus		:	$(OBJS_BONUS)
				@make make_libs
				gcc -o $(NAME) $(LIBS) $(OBJS_BONUS) $(FRAMEWORKS)

make_libs	:
			@make -j -C libft
			-@make -j -C minilibx 2>/dev/null

clean		:
			rm -f $(OBJS)
			rm -f $(OBJS_BONUS)
			@make -C libft clean

fclean		:
			rm -f $(OBJS)
			rm -f $(OBJS_BONUS)
			rm -f $(NAME)
			@make -C libft fclean
			@make -C minilibx clean

re		:	fclean all

.PHONY	:	clean fclean re all make_libs bonus
