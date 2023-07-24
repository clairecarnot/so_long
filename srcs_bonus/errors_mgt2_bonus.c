/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_mgt2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 15:05:09 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_lstremove(t_game *game, t_list **lst)
{
	t_list	*p;
	t_list	*tmp;

	p = *lst;
	while (p)
	{
		tmp = p->next;
		if ((*(t_img *)p->content).img_ptr)
			mlx_destroy_image(game->mlx_ptr, (*(t_img *)p->content).img_ptr);
		if (p->content)
			free(p->content);
		free(p);
		p = tmp;
	}
	*lst = NULL;
}

t_map	*map_init_is_null(t_map *map, int msg)
{
	if (map)
		free(map);
	if (msg == 1)
		write(2, "Error\nMap empty\n", 16);
	else if (msg == 2)
		write(2, "Error\nMap content malloc fail\n", 30);
	else if (msg == 2)
		write(2, "Error\n Fail at getting the map\n", 30);
	return (NULL);
}
