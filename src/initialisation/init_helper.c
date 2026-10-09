/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 19:41:29 by schouite          #+#    #+#             */
/*   Updated: 2026/10/07 19:48:10 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>

static void	init_delta(t_game *game)
{
	if (!game->ray.dir_x)
		game->ray.delta_x = 1e30;
	else
		game->ray.delta_x = fabs(1.0 / game->ray.dir_x);
	if (!game->ray.dir_y)
		game->ray.delta_y = 1e30;
	else
		game->ray.delta_y = fabs(1.0 / game->ray.dir_y);
}

static void	init_step_x(t_game *game)
{
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
}

static void	init_step_y(t_game *game)
{
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

void	dda_int_steps(t_game *game)
{
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
	init_delta(game);
	init_step_x(game);
	init_step_y(game);
}
