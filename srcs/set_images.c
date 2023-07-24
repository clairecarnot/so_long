/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 10:57:33 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_buffer_img(t_game *game, int sub_img_w, int sub_img_h)
{
	game->base_img.width = sub_img_w * game->map->cols;
	game->base_img.height = sub_img_h * game->map->rows;
	game->base_img.img_ptr = mlx_new_image(game->mlx_ptr,
			game->base_img.width, game->base_img.height);
	if (!game->base_img.img_ptr)
	{
		write(2, "Error\nFailed to create an image\n", 32);
		end(game);
	}
	game->base_img.addr = mlx_get_data_addr(game->base_img.img_ptr,
			&game->base_img.bpp, &game->base_img.line_len,
			&game->base_img.endian);
	if (!game->base_img.addr)
	{
		mlx_destroy_image(game->mlx_ptr, game->base_img.img_ptr);
		game->base_img.img_ptr = NULL;
		write(2, "Error\nFailed to create an address\n", 34);
		end(game);
	}
}

t_img	xpm_img(t_game *game, char *img_path, int w, int h)
{
	t_img	new_img;

	new_img.width = w;
	new_img.height = h;
	new_img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			img_path, &(new_img.width), &(new_img.height));
	if (!new_img.img_ptr)
	{
		write(2, "Error\nFailed to create xpm img\n", 31);
		end(game);
	}
	new_img.addr = mlx_get_data_addr(new_img.img_ptr,
			&new_img.bpp, &new_img.line_len,
			&new_img.endian);
	if (!new_img.addr)
	{
		mlx_destroy_image(game->mlx_ptr, new_img.img_ptr);
		new_img.img_ptr = NULL;
		write(2, "Error\nFailed to create xpm address\n", 35);
		end(game);
	}
	return (new_img);
}

void	new_img(t_img *frame, int w, int h, t_game *game)
{
	(*frame).img_ptr = mlx_new_image(game->mlx_ptr, w, h);
	if (!(*frame).img_ptr)
	{
		write(2, "Error\nFailed to create frame img\n", 33);
		return ;
	}
	(*frame).addr = mlx_get_data_addr((*frame).img_ptr, &((*frame).bpp),
			&((*frame).line_len), &((*frame).endian));
	if (!(*frame).addr)
	{
		mlx_destroy_image(game->mlx_ptr, (*frame).img_ptr);
		(*frame).img_ptr = NULL;
		write(2, "Error\nFailed to create frame addr\n", 34);
		return ;
	}
	(*frame).width = w;
	(*frame).height = h;
}

void	img_status_init(t_game *game)
{
	game->win_ptr = NULL;
	game->base_img.img_ptr = NULL;
	game->floor.img_ptr = NULL;
	game->wall.img_ptr = NULL;
	game->exit.img_ptr = NULL;
	game->player.img_ptr = NULL;
	game->collect.img_ptr = NULL;
	game->player_sprite.init = 0;
}

t_list	*ft_lstget(t_list *lst, int index)
{
	int	i;

	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	i = 0;
	while (i < index)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
