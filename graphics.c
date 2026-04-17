/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:07:34 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/17 19:52:21 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Associate every image to matching struct element, put images to scale
static int	load_textures(t_assets *a, int *size)
{
	a->grass = mlx_xpm_file_to_image(a->mlx, "./assets/Grass.xpm", &size[0],
			&size[1]);
	a->water = mlx_xpm_file_to_image(a->mlx, "./assets/Water.xpm", &size[2],
			&size[3]);
	a->player = mlx_xpm_file_to_image(a->mlx, "./assets/Player.xpm", &size[4],
			&size[5]);
	a->exit = mlx_xpm_file_to_image(a->mlx, "./assets/Exit.xpm", &size[6],
			&size[7]);
	a->collectible = mlx_xpm_file_to_image(a->mlx, "./assets/Collectible.xpm",
			&size[8], &size[9]);
	if (!a->grass || !a->water || !a->player || !a->exit || !a->collectible)
		return (ft_putstr_fd("Error.\nTexture loading failed.\n", 2), 0);
	if (!scale_assets(a, size))
		return (ft_putstr_fd("Error.\nTexture scaling failed.\n", 2), 0);
	a->tile = size[0];
	return (1);
}

// Create window
static int	create_window(t_game *game, t_assets *a)
{
	a->win = mlx_new_window(a->mlx, game->format_x * a->tile, game->format_y
			* a->tile, "so_long");
	if (!a->win)
		return (ft_putstr_fd("Error.\nmlx_new_window failed.\n", 2), 0);
	game->game_ins = a->mlx;
	return (1);
}

// Create mlx instance -> load textures -> create the window
int	init_assets(t_game *game, t_assets *a)
{
	int	size[10];

	a->mlx = mlx_init();
	if (!a->mlx)
		return (ft_putstr_fd("Error.\nmlx_init failed.\n", 2), 0);
	if (!load_textures(a, size))
		return (0);
	if (!create_window(game, a))
		return (0);
	return (1);
}
