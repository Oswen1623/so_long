/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:06:34 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/04 18:55:22 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	void *oui;
	void *window;
	(void)argc;
	(void)argv;
	oui = mlx_init();
	window = mlx_new_window(oui, 432, 432, "test");
	mlx_loop(oui);
}
