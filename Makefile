# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 11:09:30 by ccarnot           #+#    #+#              #
#    Updated: 2023/07/24 19:17:03 by ccarnot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

BONUS = so_long_bonus

CFLAGS = -g3 -Wall -Wextra -Werror
MLXFLAGS = -lX11 -lXext

INCL = -I -I./libft -I./minilib-linux

SRCS = ./srcs/main.c ./srcs/game_map_setup.c ./srcs/map_vars_setup.c ./srcs/errors_mgt1.c \
	./srcs/list_errors_map.c ./srcs/utils1_errors_map.c ./srcs/loop.c ./srcs/moves.c \
	./srcs/set_images.c ./srcs/pixels.c ./srcs/sprites.c ./srcs/errors_mgt2.c \
	./srcs/utils2_errors_map.c

SRCS_BONUS = ./srcs_bonus/main_bonus.c ./srcs_bonus/game_map_setup_bonus.c \
	./srcs_bonus/map_vars_setup_bonus.c ./srcs_bonus/errors_mgt1_bonus.c \
	./srcs_bonus/list_errors_map_bonus.c ./srcs_bonus/utils1_errors_map_bonus.c \
	./srcs_bonus/loop_bonus.c ./srcs_bonus/moves_bonus.c ./srcs_bonus/set_images_bonus.c \
	./srcs_bonus/pixels_bonus.c ./srcs_bonus/sprites_bonus.c ./srcs_bonus/errors_mgt2_bonus.c \
	./srcs_bonus/utils2_errors_map_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

LIBFT = ./libft/libft.a
LIBMLX = ./minilibx-linux/libmlx_Linux.a

$(NAME): $(OBJS)
	make lib
	make mlx
	cc -o $(NAME) $(OBJS) $(LIBFT) $(LIBMLX) $(MLXFLAGS)

$(BONUS): $(OBJS_BONUS)
	make lib
	make mlx
	cc -o $(BONUS) $(OBJS_BONUS) $(LIBFT) $(LIBMLX) $(MLXFLAGS)

all: $(NAME)

%.o: %.c
	cc $(INCL) $(CFLAGS) -o $@ -c $<

mlx:
	make -C ./minilibx-linux/ all

lib:
	make -C ./libft/ bonus

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(BONUS)

bonus: $(BONUS)

re: fclean
	make all

rebonus: fclean
	make bonus

.PHONY: all clean fclean bonus re rebonus
