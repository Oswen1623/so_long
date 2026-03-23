/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:46:14 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/23 19:36:11 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_map_counts(t_game *game)
{
	if (game->count_p != 1)
	{
		ft_putstr_fd("Error.\nExactly one player position required.\n", 2);
		return (0);
	}
	if (game->count_e != 1)
	{
		ft_putstr_fd("Error.\nExactly one exit required.\n", 2);
		return (0);
	}
	if (game->count_c < 1)
	{
		ft_putstr_fd("Error.\nAt least one collectible required.\n", 2);
		return (0);
	}
	return (1);
}


int	init_map_rectangle(int mapfiledescriptor, int *ref, char **curr_line,
		t_game *game)
{
	char	*first_line;

	first_line = get_next_line(mapfiledescriptor);
	if (!first_line)
		return (ft_putstr_fd("Error.\nCannot read file. File might be empty.\n",
				2), 0);
	*ref = line_len(first_line);
	if (!check_walls(first_line, 1))
		return (free(first_line),
			ft_putstr_fd("Error.\nThe map should be surrounded by walls.\n", 2),
			0);
	map_comp(first_line, 0, game);
	free(first_line);
	*curr_line = get_next_line(mapfiledescriptor);
	game->format_x = *ref;
	return (1);
}

void	map_rectangle(int mapfiledescriptor, t_game *game)
{
	int		ref;
	char	*curr_line;
	char	*next_line;

	game->current_y = 1;
	if (!init_map_rectangle(mapfiledescriptor, &ref, &curr_line, game))
		return ;
	while (curr_line != NULL)
	{
		next_line = get_next_line(mapfiledescriptor);
		if (!check_line_format(curr_line, next_line, ref, game))
		{
			free(curr_line);
			free(next_line);
			return ;
		}
		free(curr_line);
		game->current_y++;
		curr_line = next_line;
	}
	game->format_y = game->current_y;
}

int	map_opener(const char *mapname, t_game *game)
{
	int	mapfiledescriptor;

	if (!ft_strstr(mapname, ".ber"))
	{
		ft_putstr_fd("Error.\nWrong file format. Please use a .ber file.\n", 2);
		return (0);
	}
	mapfiledescriptor = open(mapname, O_RDONLY);
	if (mapfiledescriptor < 0)
	{
		ft_putstr_fd("Error.\nCannot open file.\n", 2);
		return (0);
	}
	map_rectangle(mapfiledescriptor, game);
	close(mapfiledescriptor);
	if (!check_map_counts(game))
		return (0);
	if (!floodfill(mapname, game))
		return (0);
	return (1);
}
