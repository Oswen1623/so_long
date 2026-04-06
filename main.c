/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:06:34 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/06 15:08:14 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
