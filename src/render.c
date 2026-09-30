/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:00:25 by schouite          #+#    #+#             */
/*   Updated: 2026/09/30 17:38:11 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx.h"
#include <stdbool.h>
#include <stdio.h>


void	draw_wall(t_data *img, int x, double perp, int colors)
{
	int	line_h;
	int	start;
	int	end;
	int	height;
	int	y;

	height = 600;
	line_h = (int)height / perp;
	start = (height / 2) - (line_h / 2);
	if (start < 0)
		start = 0;
	end = (height / 2) + (line_h / 2);
	if (end > height - 1)
		end = height - 1;
	y = start;
	while (y <= end)
	{
		my_mlx_put_to_pixel(img, x, y, colors);
		y++;
	}
}

void	draw_floor_ceiling(t_data *img)
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
			my_mlx_put_to_pixel(img, x, y, 0x0077B5FE);
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
			my_mlx_put_to_pixel(img, x, y, 0x00F5F5F5);
			x++;
		}
		y++;
	}
}

int	rendering(void)
{
	t_data img;
	void *mlx_ptr;
	void *win_ptr;
	bool flag;

	mlx_ptr = NULL;
	win_ptr = NULL;
	flag = init_mlx(&img, &mlx_ptr, &win_ptr);
	if (!flag)
		return (0);
	draw_floor_ceiling(&img);
	raycast(&img);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_key_hook(win_ptr, handle_key, NULL);
	mlx_loop(mlx_ptr);
	return (1);
}