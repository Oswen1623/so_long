/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:06:34 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/23 19:06:28 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	void	*game_ins;
	void	*window;

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
	window = mlx_new_window(game_ins, game.format_x * 75, game.format_y * 75,
			"so_long");
	(void)window;
	mlx_loop(game_ins);
}
