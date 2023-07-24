/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 12:18:18 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int argc, char **argv)
{
	t_game	game;

	check_count_args(argc);
	game.map = map_init(argv[1]);
	if (!game.map)
		return (0);
	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
		return (free_map(game.map), 0);
	if (game.map)
	{
		game.moves_count = 0;
		set_img(&game);
		prepare_to_draw(&game);
	}
	else
		end (&game);
	return (0);
}

void	set_img(t_game *game)
{
	img_status_init(game);
	create_buffer_img(game, 80, 80);
	game->wall = xpm_img(game, "./sprites/wall.xpm", 80, 80);
	game->floor = xpm_img(game, "./sprites/floor.xpm", 80, 80);
	game->player = xpm_img(game, "./sprites/player.xpm", 2400, 80);
	game->exit = xpm_img(game, "./sprites/exit.xpm", 80, 80);
	game->collect = xpm_img(game, "./sprites/collect.xpm", 80, 80);
	game->danger = xpm_img(game, "./sprites/danger.xpm", 4480, 80);
	game->player_sprite.nb_frames = 29;
	game->danger_sprite.nb_frames = 56;
	sprite_init(game, &game->player_sprite, &game->player, 20);
	game->player_sprite.init = 1;
	sprite_init(game, &game->danger_sprite, &game->danger, 10);
	game->danger_sprite.init = 1;
}

void	prepare_to_draw(t_game *game)
{
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			game->base_img.width,
			game->base_img.height, "so_long");
	if (!game->win_ptr)
	{
		write(2, "Error\nFailed to open a window\n", 30);
		end(game);
	}
	mlx_loop_hook(game->mlx_ptr, &draw, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win_ptr, 17, 0, &end, game);
	mlx_loop(game->mlx_ptr);
}

void	game_resolution(t_game *game, int outcome)
{
	if (outcome == 1)
	{
		write(1, "You WON in ", 11);
		ft_putnbr_fd(game->moves_count, 1);
		write(1, " moves !!!\n", 11);
	}
	if (outcome == -1)
		write(1, "Sorry you LOST !!!\n", 19);
	end(game);
}

int	end(t_game *game)
{
	free_map(game->map);
	free_img(game);
	if (game->player_sprite.init == 1)
	{
		if (game->player_sprite.frames)
			ft_lstremove(game, &game->player_sprite.frames);
	}
	if (game->danger_sprite.init == 1)
	{
		if (game->danger_sprite.frames)
			ft_lstremove(game, &game->danger_sprite.frames);
	}
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	if (game->mlx_ptr)
		free(game->mlx_ptr);
	exit(0);
}
