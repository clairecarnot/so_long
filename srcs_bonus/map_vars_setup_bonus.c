/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_vars_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 11:07:46 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	var_init(t_map *map)
{
	map->cols = cols_count(map->content);
	if (map->cols == -1)
		return ;
	map->exit = exit_count(map);
	if (map->exit != 1)
		return ;
	map->collect = collect_count(map);
	if (map->collect < 1)
		return ;
	map->player = player_count(map);
}

int	cols_count(char **content)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (content[0][j] && content[0][j] != '\n' && content[0][j] != '\0')
	{
		j++;
		count++;
	}
	i = 1;
	while (content[i])
	{
		j = 0;
		while (content[0][j] && content[i][j] != '\n' && content[i][j] != '\0')
			j++;
		if (j != count)
			return (write(2, "Error\nInvalid number of colums\n", 31), -1);
		i++;
	}
	return (count);
}

int	exit_count(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map->content[i])
	{
		j = 0;
		while (map->content[i][j] != '\n' && map->content[i][j] != '\0')
		{
			if (map->content[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		write(2, "Error\nNumber of Exits is not 1\n", 31);
	return (count);
}

int	collect_count(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map->content[i])
	{
		j = 0;
		while (map->content[i][j] != '\n' && map->content[i][j] != '\0')
		{
			if (map->content[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	if (count < 1)
		write(2, "Error\nNumber of Collectibles is less than 1\n", 44);
	return (count);
}

int	player_count(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map->content[i])
	{
		j = 0;
		while (map->content[i][j] != '\n' && map->content[i][j] != '\0')
		{
			if (map->content[i][j] == 'P')
			{
				count++;
				map->ppos.x = j;
				map->ppos.y = i;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		write(2, "Error\nNumber of Players is not 1\n", 34);
	return (count);
}
