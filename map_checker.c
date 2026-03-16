/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:46:14 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/16 20:50:13 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_rectangle(int mapfiledescriptor)
{
	int		ref;
	char	*curr_line;
	char	*next_line;

	if (!init_map_rectangle(mapfiledescriptor, &ref, &curr_line))
		return ;
	while (curr_line != NULL)
	{
		next_line = get_next_line(mapfiledescriptor);
		if (!check_line_format(curr_line, next_line, ref))
		{
			free(curr_line);
			free(next_line);
			return ;
		}
		free(curr_line);
		curr_line = next_line;
	}
}

void	map_opener(const char *mapname)
{
	int	mapfiledescriptor;

	if (!ft_strstr(mapname, ".ber"))
	{
		perror("Error.\nWrong file format. Please use a .ber file.\n");
		return ;
	}
	mapfiledescriptor = open(mapname, O_RDONLY);
	if (mapfiledescriptor < 0)
	{
		perror("Error.\nCannot open file.\n");
		return ;
	}
	map_rectangle(mapfiledescriptor);
	close(mapfiledescriptor);
}
