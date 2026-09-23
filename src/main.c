/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:17:40 by schouite          #+#    #+#             */
/*   Updated: 2026/09/23 14:31:29 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	(void)param;
	if (keycode == 65307)
		exit(0);
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
void dda()
{
	
}
int	main(int argc, char **argv)
{
	t_data	img;
	void	*mlx_ptr;
	void	*win_ptr;
	int		y;
	int		x;
	char	*fake_map[] = {"11111111", "10000001", "10100101", "10000001",
			"11111111", NULL};
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	perp;
	double camera_x;
	int		side;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	bool	hit;

	(void)perp;
	(void)side;
	(void)side_x;
	(void)side_y;
	(void)step_x;
	(void)step_y;
	(void)dir_x;
	(void)dir_y;
	(void)fake_map;
	(void)pos_x;
	(void)pos_y;
	(void)map_x;
	(void)map_y;
	(void)delta_x;
	(void)delta_y;
	(void)argc;
	(void)argv;
	(void)hit;
	hit = false;
	y = 0;
	dir_x = 1.0;
	dir_y = 0.0;
	if (dir_x < 0)
		step_x = -1;
	else
		step_x = 1;
	if (dir_y < 0)
		step_y = -1;
	else
		step_y = 1;
	pos_x = 1.5;
	pos_y = 1.5;
	map_x = (int)pos_x;
	map_y = (int)pos_y;
	if (dir_x == 0)
		delta_x = 1e30;
	else
		delta_x = fabs(1.0 / dir_x);
	if (dir_y == 0)
		delta_y = 1e30;
	else
		delta_y = fabs(1.0 / dir_y);
	if (step_x < 0)
		side_x = (pos_x - map_x) * delta_x;
	else
		side_x = (map_x + 1.0 - pos_x) * delta_x;
	if (step_y < 0)
		side_y = (pos_y - map_y) * delta_y;
	else
		side_y = (map_y + 1.0 - pos_y) * delta_y;
	while (!hit)
	{
		if (side_x < side_y)
		{
			side_x += delta_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_y += delta_y;
			map_y += step_y;
			side = 1;
		}
		if (fake_map[map_y][map_x] == '1')
			hit = true;
	}
	if (side == 0)
		perp = side_x - delta_x;
	else
		perp = side_y - delta_y;
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
			my_mlx_put_to_pixel(&img, x, y, 0x0077B5FE);
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
			my_mlx_put_to_pixel(&img, x, y, 0x00F5F5F5);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < 800)
	{
		camera_x = 2.0 * x / 800.0 - 1.0;
		dir_y = camera_x;
		draw_simple_wall(&img, x, perp, 0xFF0000);
		x++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_key_hook(win_ptr, handle_key, NULL);
	mlx_loop(mlx_ptr);
}

// double		pos_x = 2.5;
// double		pos_y = 2.5;
