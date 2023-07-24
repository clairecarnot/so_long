/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarnot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:06:23 by ccarnot           #+#    #+#             */
/*   Updated: 2023/07/24 11:08:11 by ccarnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	put_img_to_img(t_img dst, t_img src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src.width)
	{
		j = 0;
		while (j < src.height)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

unsigned int	get_pixel_img(t_img src, int x, int y)
{
	return (*(unsigned int *)((src.addr
			+ (y * src.line_len) + (x * src.bpp / 8))));
}

void	put_pixel_img(t_img dst, int x, int y, int color)
{
	char	*img;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < dst.width && y < dst.height)
	{
		img = dst.addr + (y * dst.line_len + x * (dst.bpp / 8));
		*(unsigned int *) img = color;
	}
}

void	put_pixel_img_sprites(t_img dst, int x, int y, int color)
{
	char	*img;

	if (x >= 0 && y >= 0 && x < dst.width && y < dst.height)
	{
		img = dst.addr + (y * dst.line_len + x * (dst.bpp / 8));
		*(unsigned int *) img = color;
	}
}
