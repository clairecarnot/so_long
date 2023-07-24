/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 14:05:28 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	draw(t_game *game)
{
	draw_background(game);
	draw_elements(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->base_img.img_ptr, 0, 0);
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
					|| game->map->content[i][j] == 'C')
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
				if (game->map->content[i][j] == 'P')
					update_sprite(game, &game->player_sprite,
						game->player_sprite.frames, (t_point){j, i});
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
	{
		game->moves_count++;
		ft_putnbr_fd(game->moves_count, 1);
		write(1, "\n", 1);
	}
	return (0);
}
