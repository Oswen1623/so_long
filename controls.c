/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:40:04 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/10 12:42:59 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	can_move(t_ctx *ctx, int next_x, int next_y, char *tile)
{
	if (next_x < 0 || next_y < 0 || next_x >= ctx->game->format_x)
		return (0);
	if (next_y >= ctx->game->format_y)
		return (0);
	*tile = ctx->game->grid[next_y][next_x];
	if (*tile == '1')
		return (0);
	return (1);
}

static void	try_move(t_ctx *ctx, int dx, int dy)
{
	int		next_x;
	int		next_y;
	char	tile;

	next_x = ctx->game->p_position_x + dx;
	next_y = ctx->game->p_position_y + dy;
	if (!can_move(ctx, next_x, next_y, &tile))
		return ;
	ctx->game->p_position_x = next_x;
	ctx->game->p_position_y = next_y;
	ctx->game->moves++;
	if (tile == 'C')
	{
		ctx->game->collected++;
		ctx->game->grid[next_y][next_x] = '0';
	}
	render_map(ctx->game, ctx->assets);
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(ctx->game->moves, 1);
	ft_putchar_fd('\n', 1);
	if (tile == 'E' && ctx->game->collected == ctx->game->count_c)
		quit_game(ctx, 0);
}

static void	dispatch_move(int keycode, t_ctx *ctx)
{
	if (keycode == KEY_UP || keycode == KEY_W)
		try_move(ctx, 0, -1);
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		try_move(ctx, 0, 1);
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		try_move(ctx, -1, 0);
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		try_move(ctx, 1, 0);
}

int	handle_keypress(int keycode, void *param)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)param;
	if (keycode == KEY_ESC)
		quit_game(ctx, 0);
	dispatch_move(keycode, ctx);
	return (0);
}
