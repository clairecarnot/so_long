/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_mgt1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/21 18:59:45 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_perror_msg(t_map *map, int n)
{
	free(map);
	if (n == 1)
		perror("Error\nThe specified map cannot be opened");
	else
		perror("Error\nThe specified map cannot be closed");
	exit(1);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->content[i])
	{
		free(map->content[i]);
		i++;
	}
	free(map->content);
	free(map);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_img(t_game *game)
{
	if (game->floor.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->floor.img_ptr);
	if (game->wall.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->wall.img_ptr);
	if (game->player.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->player.img_ptr);
	if (game->exit.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->exit.img_ptr);
	if (game->collect.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->collect.img_ptr);
	if (game->base_img.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->base_img.img_ptr);
}

int	check_map_errors(t_map *map, char *argv)
{
	if (wrong_map_format(argv))
		return (1);
	if (forbidden_chars_check(map))
		return (1);
	if (walls_surround_check(map))
		return (1);
	if (no_valid_path(map))
		return (1);
	return (0);
}
