/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:16:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/27 17:10:33 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	line_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

int	check_walls(char *s, int border_line)
{
	int	i;
	int	len;

	if (!s)
		return (0);
	len = line_len(s);
	if (len < 1)
		return (0);
	if (border_line)
	{
		i = 0;
		while (i < len)
		{
			if (s[i] != '1')
				return (0);
			i++;
		}
	}
	else if (s[0] != '1' || s[len - 1] != '1')
		return (0);
	return (1);
}

void	map_comp(char *s, int y, t_game *game)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'C')
			game->count_c++;
		else if (s[i] == 'E')
			game->count_e++;
		else if (s[i] == 'P')
		{
			game->p_position_x = i;
			game->p_position_y = y;
			game->count_p++;
		}
		i++;
	}
}

int	check_line_format(char *curr_line, char *next_line, int ref, t_game *game)
{
	int	border;
	int	len;

	border = (next_line == NULL);
	if (!check_walls(curr_line, border))
		return (ft_putstr_fd("Error.\nThe map should be surrounded by walls.\n",
				2), 0);
	map_comp(curr_line, game->current_y, game);
	len = line_len(curr_line);
	if (len != ref)
		return (ft_putstr_fd("Error.\nMap must be a rectangle.\n", 2), 0);
	return (1);
}
