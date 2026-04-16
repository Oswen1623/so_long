/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:06:34 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/10 12:42:59 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_args(int argc, char **argv)
{
	if (argc != 2 || !argv[1])
	{
		ft_putstr_fd("Error.\nNo file specified. Please specify a .ber ", 2);
		ft_putstr_fd("file as a map file.\n", 2);
		return (0);
	}
	return (1);
}

static int	init_game(char *map, t_game *game, t_assets *assets)
{
	ft_bzero(game, sizeof(t_game));
	if (!map_opener(map, game))
		return (0);
	game->collected = 0;
	game->exited = 0;
	if (!init_assets(game, assets))
		return (0);
	if (!draw_map(map, game, assets))
		return (ft_putstr_fd("Error.\nFailed to draw map.\n", 2), 1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_assets	assets;
	t_ctx		ctx;

	if (!check_args(argc, argv))
		return (0);
	if (!init_game(argv[1], &game, &assets))
		return (1);
	ctx.game = &game;
	ctx.assets = &assets;
	mlx_hook(assets.win, 2, 1L << 0, handle_keypress, &ctx);
	mlx_hook(assets.win, 17, 0, handle_destroy, &ctx);
	mlx_loop(assets.mlx);
	return (0);
}
