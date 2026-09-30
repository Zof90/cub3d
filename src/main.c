/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julesmar <julesmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:17:40 by schouite          #+#    #+#             */
/*   Updated: 2026/09/30 17:30:03 by julesmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
}			t_data;

int	handle_key(int keycode, void *param)
{
	if (keycode == 65307)
	{
		free_game(param);
		exit(0);
	}
	return (0);
}
void	my_mlx_put_to_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + ((img->line_lenght * y) + (x * img->bpp / 8));
	*(unsigned int *)dst = color;
}
void	draw_simple_wall(t_data *img, int x, double perp, int colors)
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

int	main(int argc, char **argv)
{
	t_data	img;
	void	*mlx_ptr;
	void	*win_ptr;
	int		y;
	int		x;
	t_ray	r;
	t_game	game;

	if (argc != 2)
		return (parse_error("Usage: ./cub3D <scene.cub>"));
	if (parse_file(argv[1], &game))
		return (1);
	r.p = game.player;
	x = 0;
	y = 0;
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "cub3D");
	if (win_ptr == NULL)
		return (1);
	img.img = mlx_new_image(mlx_ptr, 800, 600);
	if (!img.img)
		return (1);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_lenght,
			&img.endian);
	while (y < 300)
	{
		x = 0;
		while (x < 800)
		{
			my_mlx_put_to_pixel(&img, x, y, game.ceiling);
			x++;
		}
		y++;
	}
	y = 300;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			my_mlx_put_to_pixel(&img, x, y, game.floor);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < 800)
	{
		r.camera_x = 2.0 * x / 800.0 - 1.0;
		r.dir_x = r.p.dir_x + r.p.plane_x * r.camera_x;
		r.dir_y = r.p.dir_y + r.p.plane_y * r.camera_x;
		dda(&r, game.map);
		draw_simple_wall(&img, x, r.perp, 0xFF0000);
		x++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_key_hook(win_ptr, handle_key, &game);
	mlx_loop(mlx_ptr);
}

// double		pos_x = 2.5;
// double		pos_y = 2.5;
