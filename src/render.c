/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:00:25 by schouite          #+#    #+#             */
/*   Updated: 2026/10/05 21:48:12 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx.h"
#include <stdbool.h>
#include <stdio.h>

static int	get_tex(t_game *game, int y)
{
	int wall_y;
	int ratio;
	int tex_y;

	ratio = game->wall.height;
	wall_y = y - game->wall.start;
	
}
void	draw_wall(t_game *game, int x)
{
	int	y;
	int	pxl;

	game->wall.height = (int)HEIGHT / game->ray.perp;
	game->wall.start = (HEIGHT / 2) - (game->wall.height / 2);
	if (game->wall.start < 0)
		game->wall.start = 0;
	game->wall.end = (HEIGHT / 2) + (game->wall.height / 2);
	if (game->wall.end > HEIGHT - 1)
		game->wall.end = HEIGHT - 1;
	y = game->wall.start;
	while (y <= game->wall.end)
	{
		pxl = get_tex(game,y);
		my_mlx_put_to_pixel(game, x, y, pxl);
		y++;
	}
}

void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	x = 0;
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
	void *mlx_ptr;
	void *win_ptr;
	bool flag;

	mlx_ptr = NULL;
	win_ptr = NULL;
	flag = init_mlx(&game->data, &mlx_ptr, &win_ptr);
	if (!flag)
		return (0);
	
	draw_floor_ceiling(game);
	raycast(game);
	mlx_put_image_to_window(mlx_ptr, win_ptr, game->data.img, 0, 0);
	mlx_key_hook(win_ptr, handle_key, NULL);
	mlx_loop(mlx_ptr);
	return (1);
}
