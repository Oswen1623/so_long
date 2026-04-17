/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:40:04 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/17 19:52:33 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_tile(char c, int x, int y, t_assets *a)
{
	int	px;
	int	py;

	px = x * a->tile;
	py = y * a->tile;
	if (c == '1')
		mlx_put_image_to_window(a->mlx, a->win, a->water, px, py);
	else
		mlx_put_image_to_window(a->mlx, a->win, a->grass, px, py);
	if (c == 'E')
		mlx_put_image_to_window(a->mlx, a->win, a->exit, px, py);
	if (c == 'C')
		mlx_put_image_to_window(a->mlx, a->win, a->collectible, px, py);
}

void	render_map(t_game *game, t_assets *a)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->format_y)
	{
		x = 0;
		while (x < game->format_x)
		{
			draw_tile(game->grid[y][x], x, y, a);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(a->mlx, a->win, a->player, game->p_position_x
		* a->tile, game->p_position_y * a->tile);
}

//
int	draw_map(char *map_path, t_game *game, t_assets *a)
{
	if (!load_map_grid(map_path, game))
		return (0);
	render_map(game, a);
	return (1);
}
