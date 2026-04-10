/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:40:04 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/10 12:42:59 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_assets(t_assets *a)
{
	if (!a)
		return ;
	if (a->grass)
		mlx_destroy_image(a->mlx, a->grass);
	if (a->water)
		mlx_destroy_image(a->mlx, a->water);
	if (a->player)
		mlx_destroy_image(a->mlx, a->player);
	if (a->exit)
		mlx_destroy_image(a->mlx, a->exit);
	if (a->collectible)
		mlx_destroy_image(a->mlx, a->collectible);
	if (a->win)
		mlx_destroy_window(a->mlx, a->win);
	if (a->mlx)
	{
		mlx_destroy_display(a->mlx);
		free(a->mlx);
	}
}

void	quit_game(t_ctx *ctx, int status)
{
	if (ctx->game->grid)
		free_grid(ctx->game->grid);
	destroy_assets(ctx->assets);
	exit(status);
}

int	handle_destroy(void *param)
{
	quit_game((t_ctx *)param, 0);
	return (0);
}
