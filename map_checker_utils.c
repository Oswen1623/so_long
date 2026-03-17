/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:16:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/17 16:26:31 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	line_len(char *s)
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

void	map_comp(char *s)
{
	static long	c = 0;
	static long	e = 0;
	static long	p = 0;
	int			i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'C')
			c++;
		if (s[i] == 'E')
			e++;
		if (s[i] == 'P')
			p++;
		if (e > 1 || p > 1)
		{
			perror("Error.\nIncorrect number of exits and starting positions.");
			perror("\nPlease make sure your map contains only one of each.\n");
			return ;
		}
		i++;
	}
}

int	check_line_format(char *curr_line, char *next_line, int ref)
{
	int	border;
	int	len;

	border = (next_line == NULL);
	if (!check_walls(curr_line, border))
		return (perror("Error.\nThe map should be surrounded by walls.\n"), 0);
	map_comp(curr_line);
	len = line_len(curr_line);
	if (len != ref)
		return (perror("Error.\nMap must be a rectangle.\n"), 0);
	return (1);
}

int	init_map_rectangle(int mapfiledescriptor, int *ref, char **curr_line)
{
	char	*first_line;

	first_line = get_next_line(mapfiledescriptor);
	if (!first_line)
		return (perror("Error.\nCannot read file. File might be empty.\n"), 0);
	*ref = line_len(first_line);
	if (!check_walls(first_line, 1))
		return (free(first_line),
			perror("Error.\nThe map should be surrounded by walls.\n"), 0);
	map_comp(first_line);
	free(first_line);
	*curr_line = get_next_line(mapfiledescriptor);
	return (1);
}
