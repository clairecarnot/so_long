/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_errors_map_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 19:11:55 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_player_startpos(t_map *map, t_point *begin)
{
	int	i;
	int	j;

	i = 0;
	while (map->content[i])
	{
		j = 0;
		while (map->content[i][j] != '\n' && map->content[i][j] != '\0')
		{
			if (map->content[i][j] == 'P')
			{
				begin->x = j;
				begin->y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill1(char **tab, t_map *map)
{
	char	to_fill[4];
	t_point	size;

	map->begin.x = 0;
	map->begin.y = 0;
	init_player_startpos(map, &map->begin);
	size.x = map->cols;
	size.y = map->rows;
	to_fill[0] = 'C';
	to_fill[1] = 'P';
	to_fill[2] = '0';
	to_fill[3] = '\0';
	fill1(tab, size, map->begin, to_fill);
}

void	fill1(char **tab, t_point size, t_point cur, char *to_fill)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
		|| fill_irrelevant(tab[cur.y][cur.x], to_fill))
		return ;
	tab[cur.y][cur.x] = 'Y';
	fill1(tab, size, (t_point){cur.x - 1, cur.y}, to_fill);
	fill1(tab, size, (t_point){cur.x + 1, cur.y}, to_fill);
	fill1(tab, size, (t_point){cur.x, cur.y - 1}, to_fill);
	fill1(tab, size, (t_point){cur.x, cur.y + 1}, to_fill);
}

int	fill_irrelevant(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (0);
		i++;
	}
	return (1);
}
