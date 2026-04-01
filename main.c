/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:06:34 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/01 18:49:18 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	draw_map(char *map_path, void *mlx, void *win, void *grass,
		void *water, void *player, int tile_size)
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
			if (line[x] == '1')
				mlx_put_image_to_window(mlx, win, water, x * tile_size, y
					* tile_size);
			else
				mlx_put_image_to_window(mlx, win, grass, x * tile_size, y
					* tile_size);
			if (line[x] == 'P')
				mlx_put_image_to_window(mlx, win, player, x * tile_size, y
					* tile_size);
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
	t_game	game;
	void	*window;
	void	*grass;
	void	*water;
	void	*player;
	int		img_width;
	int		img_height;
	int		tile_size;
	int		water_w;
	int		water_h;
	int		player_w;
	int		player_h;
	char	*grass_path;
	char	*water_path;
	char	*player_path;

	grass_path = "./assets/Grass.xpm";
	water_path = "./assets/Water.xpm";
	player_path = "./assets/Player.xpm";
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
	game.game_ins = mlx_init();
	if (!game.game_ins)
		return (ft_putstr_fd("Error.\nmlx_init failed.\n", 2), 1);
	grass = mlx_xpm_file_to_image(game.game_ins, grass_path, &img_width,
			&img_height);
	water = mlx_xpm_file_to_image(game.game_ins, water_path, &water_w,
			&water_h);
	player = mlx_xpm_file_to_image(game.game_ins, player_path, &player_w,
			&player_h);
	if (!grass || !water || !player)
		return (ft_putstr_fd("Error.\nTexture loading failed.\n", 2), 1);
	tile_size = img_width;
	if (img_width <= 0 || img_height <= 0 || img_width != img_height
		|| water_w != tile_size || water_h != tile_size || player_w != tile_size
		|| player_h != tile_size)
		return (ft_putstr_fd("Error.\nTextures must all be square and same size.\n",
				2), 1);
	window = mlx_new_window(game.game_ins, game.format_x * tile_size,
			game.format_y * tile_size, "so_long");
	if (!window)
		return (ft_putstr_fd("Error.\nmlx_new_window failed.\n", 2), 1);
	if (!draw_map(argv[1], game.game_ins, window, grass, water, player,
			tile_size))
		return (ft_putstr_fd("Error.\nFailed to draw map.\n", 2), 1);
	mlx_loop(game.game_ins);
}
