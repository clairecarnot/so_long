/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_errors_map_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 19:19:58 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	flood_fill2(char **tab, t_map *map)
{
	char	to_fill[2];
	t_point	size;

	size.x = map->cols;
	size.y = map->rows;
	to_fill[0] = 'Y';
	to_fill[1] = 'E';
	fill2(tab, size, map->begin, to_fill);
}

void	fill2(char **tab, t_point size, t_point cur, char *to_fill)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
		|| fill_irrelevant(tab[cur.y][cur.x], to_fill))
		return ;
	tab[cur.y][cur.x] = 'Z';
	fill2(tab, size, (t_point){cur.x - 1, cur.y}, to_fill);
	fill2(tab, size, (t_point){cur.x + 1, cur.y}, to_fill);
	fill2(tab, size, (t_point){cur.x, cur.y - 1}, to_fill);
	fill2(tab, size, (t_point){cur.x, cur.y + 1}, to_fill);
}

int	check_path2(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][i] != '\n' && tab[i][j] != '\0')
		{
			if (tab[i][j] == 'E')
				return (write(2, "Error\nNo valid path available\n", 30), 1);
			j++;
		}
		i++;
	}
	return (0);
}
