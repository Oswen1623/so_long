/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:40:04 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/17 19:57:24 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Duplicate the line
static char	*line_dup_without_nl(char *line)
{
	int		len;
	char	*copy;

	len = line_len(line);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, line, len + 1);
	return (copy);
}

// Read and fill grid (map copy)
static int	read_grid_lines(int fd, t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	while (i < game->format_y)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		game->grid[i] = line_dup_without_nl(line);
		free(line);
		if (!game->grid[i])
			return (0);
		i++;
	}
	game->grid[i] = NULL;
	return (1);
}

// Open map -> allocate char ** -> duplicate without \n and fill grid
int	load_map_grid(char *map_path, t_game *game)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	game->grid = malloc(sizeof(char *) * (game->format_y + 1));
	if (!game->grid)
		return (close(fd), 0);
	if (!read_grid_lines(fd, game))
	{
		close(fd);
		free_grid(game->grid);
		game->grid = NULL;
		return (0);
	}
	close(fd);
	if (game->grid[game->p_position_y][game->p_position_x] == 'P')
		game->grid[game->p_position_y][game->p_position_x] = '0';
	return (1);
}
