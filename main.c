/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:06:34 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/31 14:20:01 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	draw_map(char *map_path, void *mlx, void *win, void *grass,
		void *water, void *player)
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
				mlx_put_image_to_window(mlx, win, water, x * 75, y * 75);
			else
				mlx_put_image_to_window(mlx, win, grass, x * 75, y * 75);
			if (line[x] == 'P')
				mlx_put_image_to_window(mlx, win, player, x * 75, y * 75);
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
	void	*game_ins;
	void	*window;
	void	*grass;
	void	*water;
	void	*player;
	int		img_width;
	int		img_height;
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
	game_ins = mlx_init();
	if (!game_ins)
		return (ft_putstr_fd("Error.\nmlx_init failed.\n", 2), 1);
	window = mlx_new_window(game_ins, game.format_x * 75, game.format_y * 75,
			"so_long");
	if (!window)
		return (ft_putstr_fd("Error.\nmlx_new_window failed.\n", 2), 1);
	grass = mlx_xpm_file_to_image(game_ins, grass_path, &img_width,
			&img_height);
	water = mlx_xpm_file_to_image(game_ins, water_path, &img_width,
			&img_height);
	player = mlx_xpm_file_to_image(game_ins, player_path, &img_width,
			&img_height);
	if (!grass || !water || !player)
		return (ft_putstr_fd("Error.\nTexture loading failed.\n", 2), 1);
	if (!draw_map(argv[1], game_ins, window, grass, water, player))
		return (ft_putstr_fd("Error.\nFailed to draw map.\n", 2), 1);
	mlx_loop(game_ins);
}
