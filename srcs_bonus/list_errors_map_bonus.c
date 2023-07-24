/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_errors_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 19:13:36 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	walls_surround_check(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->cols)
	{
		if (map->content[0][i] != '1' || map->content[map->rows - 1][i] != '1')
			return (write(2, "Error\nMap not surrounded by walls\n", 34), 1);
		i++;
	}
	i = 0;
	while (i < map->rows)
	{
		if (map->content[i][0] != '1' || map->content[i][map->cols - 1] != '1')
			return (write(2, "Error\nMap not surrounded by walls\n", 34), 1);
		i++;
	}
	return (0);
}

int	forbidden_chars_check(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->content[i])
	{
		j = 0;
		while (map->content[i][j] != '\n' && map->content[i][j] != '\0')
		{
			if (map->content[i][j] != '0' && map->content[i][j] != '1' &&
				map->content[i][j] != 'C' && map->content[i][j] != 'E' &&
				map->content[i][j] != 'P' && map->content[i][j] != '\n' &&
				map->content[i][j] != 'D' && map->content[i][j] != '\0')
				return (write(2, "Error\nForbidden chars in the map\n", 33), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	no_valid_path(t_map *map)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (map->rows + 1));
	if (!tab)
		return (write(2, "Error\nValid path check fail (malloc)\n", 37), 1);
	i = 0;
	while (map->content[i])
	{
		tab[i] = ft_strdup(map->content[i]);
		if (!tab[i])
			return (free_tab(tab), 1);
		i++;
	}
	tab[i] = 0;
	flood_fill1(tab, map);
	if (check_path1(tab))
		return (free_tab(tab), 1);
	flood_fill2(tab, map);
	if (check_path2(tab))
		return (free_tab(tab), 1);
	free_tab(tab);
	return (0);
}

int	check_path1(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] != '\n' && tab[i][j] != '\0')
		{
			if (tab[i][j] == 'C' || tab[i][j] == 'P')
				return (write(2, "Error\nNo valid path available\n", 30), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	wrong_map_format(char *argv)
{
	if (!ft_strnstr(argv, ".ber", ft_strlen(argv)))
	{
		write(2, "Error\nWrong map format\n", 23);
		return (1);
	}
	return (0);
}
