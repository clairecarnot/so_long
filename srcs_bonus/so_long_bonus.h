/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:32 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 19:16:28 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libft/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		line_len;
	int		endian;
}		t_img;

typedef struct s_sprite
{
	t_list	*frames;
	int		update_time;
	int		time;
	int		cur_nb;
	int		nb_frames;
	int		w;
	int		h;
	int		init;
}		t_sprite;

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_map
{
	int		rows;
	int		cols;
	int		exit;
	int		collect;
	int		player;
	char	**content;
	t_point	begin;
	t_point	ppos;
}		t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		*map;
	t_img		base_img;
	t_img		floor;
	t_img		wall;
	t_img		player;
	t_img		exit;
	t_img		collect;
	t_img		danger;
	t_sprite	player_sprite;
	t_sprite	danger_sprite;
	int			moves_count;
}		t_game;

/* Game set-up functions */
void			check_count_args(int argc);
t_map			*map_init(char *argv);
int				rows_count_part1(char *argv, t_map *map);
int				rows_count_part2(char *ptr);
void			map_perror_msg(t_map *map, int n);
char			**fill_map_content(t_map *map, char *argv, int rows);
void			free_map(t_map *map);
void			var_init(t_map *map);
int				cols_count(char **content);
int				exit_count(t_map *map);
int				collect_count(t_map *map);
int				player_count(t_map *map);
int				check_map_errors(t_map *map, char *argv);
int				walls_surround_check(t_map *map);
int				forbidden_chars_check(t_map *map);
int				no_valid_path(t_map *map);
int				check_path1(char **tab);
int				check_path2(char **tab);
int				wrong_map_format(char *argv);
void			init_player_startpos(t_map *map, t_point *begin);
void			flood_fill1(char **tab, t_map *map);
void			flood_fill2(char **tab, t_map *map);
void			fill1(char **tab, t_point size, t_point cur, char *to_fill);
int				fill_irrelevant(char c, char *s);
void			fill2(char **tab, t_point size, t_point cur, char *to_fill);
int				fill_irrelevant(char c, char *s);
void			free_tab(char **tab);
t_map			*map_init_is_null(t_map *map, int msg);

/* Game graphic-handling functions */
void			set_img(t_game *game);
void			create_buffer_img(t_game *game, int sub_img_w, int sub_img_h);
t_img			xpm_img(t_game *game, char *img_path, int w, int h);
unsigned int	get_pixel_img(t_img src, int x, int y);
void			put_img_to_img(t_img dst, t_img src, int x, int y);
void			put_pixel_img(t_img dst, int x, int y, int color);
void			prepare_to_draw(t_game *game);
int				draw(t_game *game);
int				handle_keypress(int keysym, t_game *game);
void			free_img(t_game *game);
void			draw_background(t_game *game);
void			draw_elements(t_game *game);
int				end(t_game *game);
int				remaining_collect(t_game *game);
void			move_up(t_game *game);
void			move_down(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			game_resolution(t_game *game, int end);
void			new_img(t_img *frame, int w, int h, t_game *game);
t_list			*ft_lstget(t_list *lst, int index);
void			sprite_init(t_game *game, t_sprite *sprite, t_img *img,
					int update_time);
t_img			*slice_sprite1(t_game *game, t_img *img,
					t_point coord, t_sprite *sprite);
void			slice_sprite2(t_img *frame, t_img *img,
					t_point coord, t_sprite *sprite);
void			put_pixel_img_sprites(t_img dst, int x, int y, int color);
void			update_sprite(t_game *game, t_sprite *sprite,
					t_list *frame, t_point coord);
void			create_frames(t_game *game, t_img *img, t_list *tmp,
					t_sprite *sprite);
void			ft_lstremove(t_game *game, t_list **lst);
void			img_status_init(t_game *game);
void			p_or_d(t_game *game, char c, int i, int j);

#endif
