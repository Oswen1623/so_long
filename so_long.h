/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:06:25 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/23 19:45:48 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MiniLibX/mlx.h"
# include "MiniLibX/mlx_int.h"
# include "libft/gnl/get_next_line_bonus.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_game
{
	int	p_position_x;
	int	p_position_y;
	int	format_x;
	int	format_y;
	int	current_y;
	int	count_c;
	int	count_e;
	int	count_p;
	int collected;
	int exited;
}		t_game;

char	*ft_strstr(const char *haystack, const char *needle);
int		check_walls(char *s, int border_line);
void	map_comp(char *s, int y, t_game *game);
int		check_line_format(char *curr_line, char *next_line, int ref,
			t_game *game);

int	init_map_rectangle(int mapfiledescriptor, int *ref, char **curr_line,
			t_game *game);
void	map_rectangle(int mapfiledescriptor, t_game *game);
int     map_opener(const char *mapname, t_game *game);

char	**create_grid(const char *mapname, t_game *game);
void	free_grid(char **grid);
int	floodfill(const char *mapname, t_game *game);
int	line_len(char *s);

#endif