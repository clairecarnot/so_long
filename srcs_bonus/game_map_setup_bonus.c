/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map_setup_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 15:03:53 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_count_args(int argc)
{
	if (argc > 2)
	{
		write(2, "Error\n", 6);
		write(2, "Too many arguments !\n", 21);
		exit(1);
	}
	else if (argc < 2)
	{
		write(2, "Error\n", 6);
		write(2, "Map is missing !\n", 17);
		exit(1);
	}
	else
		return ;
}

t_map	*map_init(char *argv)
{
	t_map	*map;

	map = malloc(sizeof(t_map) * 1);
	if (!map)
		return (write(2, "Error\nMap malloc KO\n", 20), NULL);
	map->rows = rows_count_part1(argv, map);
	if (map->rows < 1)
		return (map_init_is_null(map, 1));
	map->content = malloc(sizeof(char *) * (map->rows + 1));
	if (!map->content)
		return (map_init_is_null(map, 2));
	map->content = fill_map_content(map, argv, map->rows);
	if (!map->content)
		return (map_init_is_null(map, 3));
	var_init(map);
	if (map->cols == -1 || map->exit != 1 || map->collect < 1
		|| map->player != 1)
		return (free_map(map), NULL);
	if (check_map_errors(map, argv))
		return (free_map(map), NULL);
	return (map);
}

char	**fill_map_content(t_map *map, char *argv, int rows)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		map_perror_msg(map, 1);
	while (i < rows)
	{
		map->content[i] = get_next_line(fd, 0);
		if (!map->content[i])
			return (free_map(map), NULL);
		i++;
	}
	get_next_line(fd, 1);
	map->content[i] = 0;
	if (close(fd) == -1)
		map_perror_msg(map, 2);
	return (map->content);
}

int	rows_count_part1(char *argv, t_map *map)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		map_perror_msg(map, 1);
	while (1)
	{
		line = get_next_line(fd, 0);
		if (!line)
			break ;
		count += rows_count_part2(line);
	}
	if (close(fd) == -1)
		map_perror_msg(map, 2);
	return (count);
}

int	rows_count_part2(char *ptr)
{
	int		count;
	char	*line;

	line = ptr;
	count = 0;
	while (*line)
	{
		if (*line == '\n' || *line == '\0')
			count++;
		line++;
	}
	free(ptr);
	return (count);
}
