/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:06:25 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/16 20:50:13 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "MiniLibX/mlx.h"
# include "MiniLibX/mlx_int.h"
# include "libft/gnl/get_next_line_bonus.h"
# include "libft/libft.h"

char	*ft_strstr(const char *haystack, const char *needle);
int		check_walls(char *s, int border_line);
void	map_comp(char *s);
int		check_line_format(char *curr_line, char *next_line, int ref);
int		init_map_rectangle(int mapfiledescriptor, int *ref, char **curr_line);
void	map_rectangle(int mapfiledescriptor);
void	map_opener(const char *mapname);

#endif