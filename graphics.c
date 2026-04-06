/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:07:34 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/06 20:41:03 by lucinguy         ###   ########.fr       */
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
	if (c == 'P')
		mlx_put_image_to_window(a->mlx, a->win, a->player, px, py);
	if (c == 'E')
		mlx_put_image_to_window(a->mlx, a->win, a->exit, px, py);
	if (c == 'C')
		mlx_put_image_to_window(a->mlx, a->win, a->collectible, px, py);
}

int	init_assets(t_game *game, t_assets *a)
{
	int	size[10];

	a->mlx = mlx_init();
	if (!a->mlx)
		return (ft_putstr_fd("Error.\nmlx_init failed.\n", 2), 0);
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
	a->tile = size[0];
	a->win = mlx_new_window(a->mlx, game->format_x * a->tile, game->format_y
			* a->tile, "so_long");
	if (!a->win)
		return (ft_putstr_fd("Error.\nmlx_new_window failed.\n", 2), 0);
	game->game_ins = a->mlx;
	return (1);
}

int	draw_map(char *map_path, t_assets *a)
{
	int		fd;
	int		x;
	int		y;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		x = 0;
		while (line[x] && line[x] != '\n')
		{
			draw_tile(line[x], x, y, a);
			x++;
		}
		free(line);
		y++; 
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
