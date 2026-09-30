/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julesmar <julesmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 09:32:01 by julesmar          #+#    #+#             */
/*   Updated: 2026/09/30 17:27:14 by julesmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	is_void(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return (1);
	return (game->map[y][x] == ' ');
}

static int	is_leak(t_game *game, int x, int y)
{
	if (game->map[y][x] != '0')
		return (0);
	return (is_void(game, x - 1, y) || is_void(game, x + 1, y)
		|| is_void(game, x, y - 1) || is_void(game, x, y + 1));
}

int	check_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (is_leak(game, x, y))
				return (parse_error("Map is not closed by walls"));
			x++;
		}
		y++;
	}
	return (0);
}
