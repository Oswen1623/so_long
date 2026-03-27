/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:34:16 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/27 17:09:55 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	flood(char **grid, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->format_x || y >= game->format_y)
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (0);
	if (grid[y][x] == 'C')
		game->collected++;
	if (grid[y][x] == 'E')
		game->exited++;
	grid[y][x] = 'V';
	flood(grid, x + 1, y, game);
	flood(grid, x - 1, y, game);
	flood(grid, x, y + 1, game);
	flood(grid, x, y - 1, game);
	return (1);
}

static int	read_grid_lines(char **grid, int fd, t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	while (i < game->format_y)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		grid[i] = ft_strdup(line);
		free(line);
		if (!grid[i])
			break ;
		i++;
	}
	grid[i] = NULL;
	return (i == game->format_y);
}

static char	**create_grid(const char *mapname, t_game *game)
{
	int		fd;
	char	**grid;

	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		return (NULL);
	grid = malloc(sizeof(char *) * (game->format_y + 1));
	if (!grid)
		return (close(fd), NULL);
	if (!read_grid_lines(grid, fd, game))
	{
		free_grid(grid);
		return (close(fd), NULL);
	}
	close(fd);
	return (grid);
}

/*
** Libère la grille allouée
*/
void	free_grid(char **grid)
{
	int	i;

	i = 0;
	if (!grid)
		return ;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

/*
** floodfill principal : copie la map, lance flood, vérifie faisabilité
*/
int	floodfill(const char *mapname, t_game *game)
{
	char	**grid;
	int		x;
	int		y;

	x = game->p_position_x;
	y = game->p_position_y;
	grid = create_grid(mapname, game);
	if (!grid)
		return (ft_putstr_fd("Error.\nFloodfill: map copy failed.\n", 2), 0);
	flood(grid, x, y, game);
	if (game->collected < game->count_c)
		return (ft_putstr_fd("Error.\nFloodfill: unreachable collectible.\n",
				2), 0);
	if (game->exited != 1)
		return (ft_putstr_fd("Error.\nFloodfill: unreachable exit.\n", 2), 0);
	free_grid(grid);
	return (1);
}
