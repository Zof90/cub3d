/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 16:33:40 by schouite          #+#    #+#             */
/*   Updated: 2026/10/05 21:41:25 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>
#include <stdbool.h>

static void	dda_int_steps(t_game *game)
{
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
	if (!game->ray.dir_x)
		game->ray.delta_x = 1e30;
	else
		game->ray.delta_x = fabs(1.0 / game->ray.dir_x);
	if (!game->ray.dir_y)
		game->ray.delta_y = 1e30;
	else
		game->ray.delta_y = fabs(1.0 / game->ray.dir_y);
	if (game->ray.dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_x = (game->player.pos_x - game->ray.map_x)
			* game->ray.delta_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_x = (game->ray.map_x + 1.0 - game->player.pos_x)
			* game->ray.delta_x;
	}
	if (game->ray.dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_y = (game->player.pos_y - game->ray.map_y)
			* game->ray.delta_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_y = (game->ray.map_y + 1.0 - game->player.pos_y)
			* game->ray.delta_y;
	}
}
void	dda(t_game *game)
{
	bool	hit;

	hit = false;
	dda_int_steps(game);
	while (!hit)
	{
		if (game->ray.side_x < game->ray.side_y)
		{
			game->ray.side_x += game->ray.delta_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_y += game->ray.delta_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (game->map[game->ray.map_y][game->ray.map_x] == '1')
			hit = 1;
	}
	if (!game->ray.side)
		game->ray.perp = game->ray.side_x - game->ray.delta_x;
	else
		game->ray.perp = game->ray.side_y - game->ray.delta_y;
}
void	raycast(t_game *game)
{
	int	x;
	
	x = 0;
	while (x < WIDTH)
	{
		game->ray.camera_x = 2.0 * x / 800.0 - 1.0;
		game->ray.dir_x = game->player.dir_x + game->player.plane_x
			* game->ray.camera_x;
		game->ray.dir_y = game->player.dir_y + game->player.plane_y
			* game->ray.camera_x;
		dda(game);
		draw_wall(game, x);
		x++;
	}
}
