/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:06:34 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/04 18:58:40 by lucinguy         ###   ########.fr       */
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
}

static int	init_assets(t_game *game, t_assets *a)
{
	int	size[6];

	a->mlx = mlx_init();
	if (!a->mlx)
		return (ft_putstr_fd("Error.\nmlx_init failed.\n", 2), 0);
	a->grass = mlx_xpm_file_to_image(a->mlx, "./assets/Grass.xpm", &size[0],
			&size[1]);
	a->water = mlx_xpm_file_to_image(a->mlx, "./assets/Water.xpm", &size[2],
			&size[3]);
	a->player = mlx_xpm_file_to_image(a->mlx, "./assets/Player.xpm", &size[4],
			&size[5]);
	if (!a->grass || !a->water || !a->player)
		return (ft_putstr_fd("Error.\nTexture loading failed.\n", 2), 0);
	a->tile = size[0];
	if (size[0] <= 0 || size[0] != size[1] || size[2] != a->tile
		|| size[3] != a->tile || size[4] != a->tile || size[5] != a->tile)
		return (ft_putstr_fd("Error.\nTextures must be square and same size.\n",
				2), 0);
	a->win = mlx_new_window(a->mlx, game->format_x * a->tile, game->format_y
			* a->tile, "so_long");
	if (!a->win)
		return (ft_putstr_fd("Error.\nmlx_new_window failed.\n", 2), 0);
	game->game_ins = a->mlx;
	return (1);
}

static int	draw_map(char *map_path, t_assets *a)
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

int	main(int argc, char **argv)
{
	t_game		game;
	t_assets	assets;

	(void)argc;
	if (!argv[1])
	{
		ft_putstr_fd("Error.\nNo file specified. Please specify a .ber ", 2);
		ft_putstr_fd("file as a map file.\n", 2);
		return (0);
	}
	ft_bzero(&game, sizeof(t_game));
	if (!map_opener(argv[1], &game))
		return (1);
	if (!init_assets(&game, &assets))
		return (1);
	if (!draw_map(argv[1], &assets))
		return (ft_putstr_fd("Error.\nFailed to draw map.\n", 2), 1);
	mlx_loop(assets.mlx);
	return (0);
}
