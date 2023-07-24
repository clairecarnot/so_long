/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/12 16:31:19 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	remaining_collect(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->content[i])
	{
		j = 0;
		while (game->map->content[i][j] && game->map->content[i][j] != '\n')
		{
			if (game->map->content[i][j] == 'C')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	move_down(t_game *game)
{
	int	i;
	int	j;

	j = game->map->ppos.x;
	i = game->map->ppos.y;
	if (game->map->content[i + 1][j] && game->map->content[i + 1][j] != '\n')
	{
		if (game->map->content[i + 1][j] == 'E' && !remaining_collect(game))
			game_resolution(game, 1);
		else if (game->map->content[i + 1][j] == 'C'
			|| game->map->content[i + 1][j] == '0')
		{
			game->map->content[i][j] = '0';
			game->map->content[i + 1][j] = 'P';
			game->map->ppos.y = i + 1;
		}
	}
}

void	move_left(t_game *game)
{
	int	i;
	int	j;

	j = game->map->ppos.x;
	i = game->map->ppos.y;
	if (game->map->content[i][j - 1] && game->map->content[i][j - 1] != '\n')
	{
		if (game->map->content[i][j - 1] == 'E' && !remaining_collect(game))
			game_resolution(game, 1);
		else if (game->map->content[i][j - 1] == 'C'
			|| game->map->content[i][j - 1] == '0')
		{
			game->map->content[i][j] = '0';
			game->map->content[i][j - 1] = 'P';
			game->map->ppos.x = j - 1;
		}
	}
}

void	move_right(t_game *game)
{
	int	i;
	int	j;

	j = game->map->ppos.x;
	i = game->map->ppos.y;
	if (game->map->content[i][j + 1] && game->map->content[i][j + 1] != '\n')
	{
		if (game->map->content[i][j + 1] == 'E' && !remaining_collect(game))
			game_resolution(game, 1);
		else if (game->map->content[i][j + 1] == 'C'
			|| game->map->content[i][j + 1] == '0')
		{
			game->map->content[i][j] = '0';
			game->map->content[i][j + 1] = 'P';
			game->map->ppos.x = j + 1;
		}
	}
}

void	move_up(t_game *game)
{
	int	i;
	int	j;

	j = game->map->ppos.x;
	i = game->map->ppos.y;
	if (game->map->content[i - 1][j] && game->map->content[i - 1][j] != '\n')
	{
		if (game->map->content[i - 1][j] == 'E' && !remaining_collect(game))
			game_resolution(game, 1);
		else if (game->map->content[i - 1][j] == 'C'
			|| game->map->content[i - 1][j] == '0')
		{
			game->map->content[i][j] = '0';
			game->map->content[i - 1][j] = 'P';
			game->map->ppos.y = i - 1;
		}
	}
}
