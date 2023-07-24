/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 14:23:46 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	draw(t_game *game)
{
	char	*moves_count;

	moves_count = ft_itoa(game->moves_count);
	draw_background(game);
	draw_elements(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->base_img.img_ptr, 0, 0);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 20, 30,
		(int)0x0000ff, "moves count:");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 40, 40,
		(int)0x0000ff, moves_count);
	free(moves_count);
	return (0);
}

void	draw_background(t_game *game)
{
	int	i;
	int	j;

	if (game->win_ptr)
	{
		i = 0;
		while (game->map->content[i])
		{
			j = 0;
			while (game->map->content[i][j] != '\n' && game->map->content[i][j])
			{
				if (game->map->content[i][j] == '1')
					put_img_to_img(game->base_img, game->wall, j * 80, i * 80);
				if (game->map->content[i][j] == '0'
					|| game->map->content[i][j] == 'P'
					|| game->map->content[i][j] == 'E'
					|| game->map->content[i][j] == 'C'
					|| game->map->content[i][j] == 'D')
					put_img_to_img(game->base_img, game->floor, j * 80, i * 80);
				j++;
			}
			i++;
		}
	}
}

void	draw_elements(t_game *game)
{
	int	i;
	int	j;

	if (game->win_ptr)
	{
		i = 0;
		while (game->map->content[i])
		{
			j = 0;
			while (game->map->content[i][j] && game->map->content[i][j] != '\n')
			{
				if (game->map->content[i][j] == 'P'
					|| game->map->content[i][j] == 'D')
					p_or_d(game, game->map->content[i][j], i, j);
				if (game->map->content[i][j] == 'E')
					put_img_to_img(game->base_img,
						game->exit, j * 80, i * 80);
				if (game->map->content[i][j] == 'C')
					put_img_to_img(game->base_img,
						game->collect, j * 80, i * 80);
				j++;
			}
			i++;
		}
	}
}

void	p_or_d(t_game *game, char c, int i, int j)
{
	if (c == 'P')
		update_sprite(game, &game->player_sprite,
			game->player_sprite.frames, (t_point){j, i});
	if (c == 'D')
		update_sprite(game, &game->danger_sprite,
			game->danger_sprite.frames, (t_point){j, i});
}

int	handle_keypress(int keysym, t_game *game)
{
	t_point		old_ppos;

	old_ppos.x = game->map->ppos.x;
	old_ppos.y = game->map->ppos.y;
	if (keysym == XK_Escape)
		end(game);
	if (keysym == XK_w)
		move_up(game);
	if (keysym == XK_s)
		move_down(game);
	if (keysym == XK_a)
		move_left(game);
	if (keysym == XK_d)
		move_right(game);
	if (old_ppos.x != game->map->ppos.x
		|| old_ppos.y != game->map->ppos.y)
		game->moves_count++;
	return (0);
}
