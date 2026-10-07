/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:00:25 by schouite          #+#    #+#             */
/*   Updated: 2026/10/07 19:28:59 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx.h"
#include <stdbool.h>
#include <stdio.h>

static int	get_tex_y(t_game *game, int y)
{
	int	wall_y;
	int	tex_y;
	double	ratio;

	tex_y = 0;
	ratio = (double)game->wall.height / game->texture->height;
	wall_y = y - game->wall.start;
	tex_y = wall_y / ratio;
	return (tex_y);
}
static int	get_tex_x(t_game *game, int face)
{
	double	wall_x;
	int		wall_width;
	double		ratio;
	double		impact_y;
	int		tex_x;

	wall_width = 1;
	ratio = (double)wall_width / game->texture[face].width;
	if (game->ray.side == 0)
	{
		// printf("1\n");
		impact_y = game->player.pos_y + (game->ray.perp * game->ray.dir_y);
		wall_x = (double)impact_y - game->ray.map_y;
	}
	if (game->ray.side == 1)
	{
		impact_y = game->player.pos_x + (game->ray.perp * game->ray.dir_x);
		wall_x = (double)impact_y - game->ray.map_x;
	}
	tex_x = wall_x / ratio;
	return (tex_x);
}
void	draw_wall(t_game *game, int x)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	pxl;
	int	face;

	game->wall.height = (int)HEIGHT / game->ray.perp;
	game->wall.start = (HEIGHT / 2) - (game->wall.height / 2);
	if (game->wall.start < 0)
		game->wall.start = 0;
	game->wall.end = (HEIGHT / 2) + (game->wall.height / 2);
	if (game->wall.end > HEIGHT - 1)
		game->wall.end = HEIGHT - 1;
	y = game->wall.start;
	face = get_texture_face(game);
	init_one_texture(game, face);
	tex_x = get_tex_x(game, face);
	while (y <= game->wall.end)
	{
		tex_y = get_tex_y(game, y);
		pxl = get_texture_pixel(game, tex_x, tex_y, face);
		my_mlx_put_to_pixel(game, x, y, pxl);
		y++;
	}
}

void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < (HEIGHT / 2))
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_put_to_pixel(game, x, y, game->ceiling);
			x++;
		}
		y++;
	}
	y = (HEIGHT / 2);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_put_to_pixel(game, x, y, game->floor);
			x++;
		}
		y++;
	}
}

int	rendering(t_game *game)
{
	bool	flag;

	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	flag = init_mlx(game);
	if (!flag)
		return (0);
	draw_floor_ceiling(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->data.img, 0, 0);
	mlx_key_hook(game->win_ptr, handle_key, NULL);
	mlx_loop(game->mlx_ptr);
	return (1);
}
