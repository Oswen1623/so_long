/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_scale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 13:12:24 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/10 14:17:57 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_block(t_img *dst, int x, int y, unsigned int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < SCALE_FACTOR)
	{
		dx = 0;
		while (dx < SCALE_FACTOR)
		{
			*(unsigned int *)(dst->addr + (y + dy) * dst->line_len
					+ (x + dx) * (dst->bpp / 8)) = color;
			dx++;
		}
		dy++;
	}
}

static void	copy_scaled(t_img *src, t_img *dst)
{
	int			x;
	int			y;
	int			color;

	y = -1;
	while (++y < src->h)
	{
		x = -1;
		while (++x < src->w)
		{
			color = *(unsigned int *)(src->addr + y * src->line_len + x
					* (src->bpp / 8));
			put_block(dst, x * SCALE_FACTOR, y * SCALE_FACTOR, color);
		}
	}
}

static int	init_scaled_data(void *mlx, void **img_ptr, t_img *src, t_img *dst)
{
	void	*new_img;

	new_img = mlx_new_image(mlx, src->w * SCALE_FACTOR, src->h * SCALE_FACTOR);
	if (!new_img)
		return (0);
	src->addr = mlx_get_data_addr(*img_ptr, &src->bpp, &src->line_len,
			&src->endian);
	dst->w = src->w * SCALE_FACTOR;
	dst->h = src->h * SCALE_FACTOR;
	dst->addr = mlx_get_data_addr(new_img, &dst->bpp, &dst->line_len,
			&dst->endian);
	copy_scaled(src, dst);
	mlx_destroy_image(mlx, *img_ptr);
	*img_ptr = new_img;
	return (1);
}

static int	scale_one(void *mlx, void **img_ptr, int *w, int *h)
{
	t_img	src;
	t_img	dst;

	src.w = *w;
	src.h = *h;
	if (!init_scaled_data(mlx, img_ptr, &src, &dst))
		return (0);
	*w = dst.w;
	*h = dst.h;
	return (1);
}

int	scale_assets(t_assets *a, int *size)
{
	if (!scale_one(a->mlx, &a->grass, &size[0], &size[1]))
		return (0);
	if (!scale_one(a->mlx, &a->water, &size[2], &size[3]))
		return (0);
	if (!scale_one(a->mlx, &a->player, &size[4], &size[5]))
		return (0);
	if (!scale_one(a->mlx, &a->exit, &size[6], &size[7]))
		return (0);
	if (!scale_one(a->mlx, &a->collectible, &size[8], &size[9]))
		return (0);
	return (1);
}
