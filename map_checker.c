/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:46:14 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/06 20:05:07 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_rectangle(int mapfiledescriptor)
{
	int		ref;
	int		len;
	char	*curr_line;
	char	*first_line;

	first_line = get_next_line(mapfiledescriptor);
	if (!first_line)
	{
		perror("Cannot read file.");
		return ;
	}
	ref = ft_strlen(first_line);
	free(first_line);
	curr_line = get_next_line(mapfiledescriptor);
	while (curr_line != NULL)
	{
		len = ft_strlen(curr_line);
		if (len != ref)
			perror("Map must be a rectangle.");
		free(curr_line);
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
