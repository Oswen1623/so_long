/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:46:14 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/16 18:42:16 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_walls(void)
{
	int	i;

	i = 0;
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
		if (s[i] == 'c')
			c++;
		if (s[i] == 'e')
			e++;
		if (s[i] == 'p')
			p++;
		if (e > 1 || p > 1)
		{
			perror("Incorrect number of exits and starting position. Please make sure your map contains only one of each.");
			return ;
		}
		i++;
	}
}

void	map_rectangle(int mapfiledescriptor)
{
	int			ref;
	static int	len;
	char		*curr_line;
	char		*first_line;
	static int	lines;

	lines = 0;
	first_line = get_next_line(mapfiledescriptor);
	if (!first_line)
		return (perror("Cannot read file."));
	ref = ft_strlen(first_line);
	free(first_line);
	curr_line = get_next_line(mapfiledescriptor);
	while (curr_line != NULL)
	{
		map_comp(curr_line);
		len = ft_strlen(curr_line);
		if (len != ref)
			perror("Map must be a rectangle.");
		free(curr_line);
		lines++;
		curr_line = get_next_line(mapfiledescriptor);
	}
}

void	map_opener(const char *mapname)
{
	int	mapfiledescriptor;

	if (!ft_strstr(mapname, ".ber"))
	{
		perror("Wrong file format. Please use a .ber file.");
		return ;
	}
	mapfiledescriptor = open(mapname, O_RDONLY);
	if (mapfiledescriptor < 0)
	{
		perror("Cannot open file.");
		return ;
	}
	map_rectangle(mapfiledescriptor);
	close(mapfiledescriptor);
}
