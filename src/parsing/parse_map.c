/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julesmar <julesmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 19:03:32 by julesmar          #+#    #+#             */
/*   Updated: 2026/09/30 17:28:36 by julesmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "libft.h"
#include <stdlib.h>

static int	measure_map(char **lines, t_game *game)
{
	int	i;
	int	len;

	i = 0;
	while (lines[i] && !is_blank(lines[i]))
	{
		len = ft_strlen(lines[i]);
		if (len > game->map_width)
			game->map_width = len;
		i++;
	}
	game->map_height = i;
	while (lines[i] && is_blank(lines[i]))
		i++;
	if (lines[i])
		return (parse_error("Map must be last and have no empty line"));
	if (!game->map_height)
		return (parse_error("Map is missing"));
	return (0);
}

/* Rows are padded with spaces so the map is a rectangle. */
static int	copy_map(char **lines, t_game *game)
{
	int	y;

	game->map = ft_calloc(game->map_height + 1, sizeof(char *));
	if (!game->map)
		return (parse_error("Memory allocation failed"));
	y = 0;
	while (y < game->map_height)
	{
		game->map[y] = malloc(game->map_width + 1);
		if (!game->map[y])
			return (parse_error("Memory allocation failed"));
		ft_memset(game->map[y], ' ', game->map_width);
		game->map[y][game->map_width] = '\0';
		ft_memcpy(game->map[y], lines[y], ft_strlen(lines[y]));
		y++;
	}
	return (0);
}

static void	set_player(t_player *p, char c, int x, int y)
{
	p->pos_x = x + 0.5;
	p->pos_y = y + 0.5;
	p->dir_x = (c == 'E') - (c == 'W');
	p->dir_y = (c == 'S') - (c == 'N');
	p->plane_x = -p->dir_y * 0.66;
	p->plane_y = p->dir_x * 0.66;
}

static int	scan_map(t_game *game)
{
	int	x;
	int	y;
	int	players;

	players = 0;
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			if (!ft_strchr(" 01NSEW", game->map[y][x]))
				return (parse_error("Invalid character in map"));
			if (!ft_strchr("NSEW", game->map[y][x]))
				continue ;
			set_player(&game->player, game->map[y][x], x, y);
			game->map[y][x] = '0';
			players++;
		}
	}
	if (players != 1)
		return (parse_error("Map must contain exactly one player"));
	return (0);
}

int	parse_map(char **lines, t_game *game)
{
	if (measure_map(lines, game) || copy_map(lines, game))
		return (1);
	if (scan_map(game))
		return (1);
	return (check_walls(game));
}
