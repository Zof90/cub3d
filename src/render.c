/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:00:25 by schouite          #+#    #+#             */
/*   Updated: 2026/10/01 18:53:10 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx.h"
#include <stdbool.h>
#include <stdio.h>

void	draw_wall(t_game *game, int x)
{
	int	line_h;
	int	start;
	int	end;
	int	height;
	int	y;

	height = 600;
	line_h = (int)height / game->ray.perp;
	start = (height / 2) - (line_h / 2);
	if (start < 0)
		start = 0;
	end = (height / 2) + (line_h / 2);
	if (end > height - 1)
		end = height - 1;
	y = start;
	while (y <= end)
	{
		my_mlx_put_to_pixel(game, x, y, 0xFF0000);
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