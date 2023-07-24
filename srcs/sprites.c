/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:16:05 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 10:58:42 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sprite_init(t_game *game, t_sprite *sprite, t_img *img, int update_time)
{
	t_list	*tmp;

	sprite->frames = malloc(sizeof(t_list));
	if (!sprite->frames)
	{
		sprite->frames = NULL;
		write(2, "Error\nSprite creation failed\n", 29);
		end(game);
	}
	sprite->update_time = update_time;
	sprite->w = 80;
	sprite->h = 80;
	sprite->time = 0;
	sprite->cur_nb = 0;
	sprite->frames->content = slice_sprite1(game, img, (t_point){0, 0}, sprite);
	sprite->frames->next = NULL;
	tmp = sprite->frames;
	create_frames(game, img, tmp, sprite);
}

void	create_frames(t_game *game, t_img *img, t_list *tmp, t_sprite *sprite)
{
	int		i;
	t_point	coord;

	i = 0;
	coord.x = sprite->w;
	coord.y = 0;
	while (i < sprite->nb_frames)
	{
		tmp->next = ft_lstnew(slice_sprite1(game, img, coord, sprite));
		if (!tmp->next)
			end(game);
		tmp = tmp->next;
		if (coord.x > img->width)
		{
			coord.x = 0;
			coord.y += sprite->h;
		}
		coord.x += sprite->w;
		i++;
	}
}

t_img	*slice_sprite1(t_game *game, t_img *img, t_point coord,
		t_sprite *sprite)
{
	t_img	*frame;

	frame = ft_calloc(sizeof(t_img), 1);
	if (!frame)
	{
		free(sprite->frames);
		sprite->frames = NULL;
		write(2, "Error\nFailed to create a frame\n", 31);
		end(game);
	}
	new_img(frame, sprite->w, sprite->h, game);
	if (!(*frame).img_ptr)
	{
		free(frame);
		free(sprite->frames);
		sprite->frames = NULL;
		end(game);
	}
	slice_sprite2(frame, img, coord, sprite);
	return (frame);
}

void	slice_sprite2(t_img *frame, t_img *img, t_point coord, t_sprite *sprite)
{
	int	i;
	int	j;

	i = 0;
	while (i < sprite->w)
	{
		j = 0;
		while (j < sprite->h)
		{
			put_pixel_img_sprites(*frame, j, i,
				get_pixel_img(*img, coord.x + j, coord.y + i));
			j++;
		}
		i++;
	}
}

void	update_sprite(t_game *game, t_sprite *sprite,
		t_list *frame, t_point coord)
{
	t_list	*tmp;
	t_img	img;

	tmp = frame;
	sprite->time++;
	if (sprite->time == sprite->update_time)
	{
		sprite->time = 0;
		sprite->cur_nb++;
		sprite->cur_nb %= ft_lstsize(frame);
		img = *(t_img *)ft_lstget(tmp, sprite->cur_nb)->content;
		put_img_to_img(game->base_img, img,
			coord.x * sprite->w, coord.y * sprite->h);
	}
	else
	{
		img = *(t_img *)ft_lstget(tmp, sprite->cur_nb)->content;
		put_img_to_img(game->base_img, img,
			coord.x * sprite->w, coord.y * sprite->h);
	}
}
