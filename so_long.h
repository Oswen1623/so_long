/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:06:25 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/10 16:02:57 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MiniLibX/mlx.h"
# include "libft/gnl/get_next_line_bonus.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_game
{
	void		*game_ins;
	char		**grid;
	int			p_position_x;
	int			p_position_y;
	int			format_x;
	int			format_y;
	int			current_y;
	int			count_c;
	int			count_e;
	int			count_p;
	int			moves;
	int			collected;
	int			exited;
}				t_game;

typedef struct s_assets
{
	void		*mlx;
	void		*win;
	void		*grass;
	void		*water;
	void		*player;
	void		*exit;
	void		*collectible;
	int			tile;
}				t_assets;

typedef struct s_ctx
{
	t_game		*game;
	t_assets	*assets;
}				t_ctx;

typedef struct s_img
{
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			w;
	int			h;
}				t_img;

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define SCALE_FACTOR 2

char			*ft_strstr(const char *haystack, const char *needle);
int				check_walls(char *s, int border_line);
int				map_comp(char *s, int y, t_game *game);
int				check_line_format(char *curr_line, char *next_line, int ref,
					t_game *game);
void			gnl_drain_fd(int fd);

int				init_map_rectangle(int mapfiledescriptor, int *ref,
					char **curr_line, t_game *game);
void			map_rectangle(int mapfiledescriptor, t_game *game);
int				map_opener(const char *mapname, t_game *game);
int				init_assets(t_game *game, t_assets *a);
int				scale_assets(t_assets *a, int *size);
int				load_map_grid(char *map_path, t_game *game);
void			render_map(t_game *game, t_assets *a);
int				draw_map(char *map_path, t_game *game, t_assets *a);
void			quit_game(t_ctx *ctx, int status);
int				handle_keypress(int keycode, void *param);
int				handle_destroy(void *param);

void			free_grid(char **grid);
int				floodfill(const char *mapname, t_game *game);
int				line_len(char *s);

#endif