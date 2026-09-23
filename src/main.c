/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:17:40 by schouite          #+#    #+#             */
/*   Updated: 2026/09/23 20:30:41 by schouite         ###   ########.fr       */
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
void	dda_int_steps(t_ray *r)
{
	if (!r->dir_x)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->dir_x);
	if (!r->dir_y)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->dir_y);
	r->map_x = (int)r->p.pos_x;
	r->map_y = (int)r->p.pos_y;
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (r->p.pos_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - r->p.pos_x) * r->delta_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (r->p.pos_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - r->p.pos_y) * r->delta_y;
	}
}
void	dda(t_ray *r, char **map)
{
	bool	hit;

	hit = false;
	dda_int_steps(r);
	while (!hit)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (map[r->map_y][r->map_x] == '1')
			hit = 1;
	}
	if (!r->side)
		r->perp = r->side_x - r->delta_x;
	else
		r->perp = r->side_y - r->delta_y;
}
int	main(int argc, char **argv)
{
	t_data	img;
	void	*mlx_ptr;
	void	*win_ptr;
	int		y;
	int		x;
	t_ray	r;
	char	*fake_map[] = {"11111111", "10000001", "10100101", "10000001",
			"11111111", NULL};

	r.p.dir_x = -1.0;
	r.p.dir_y = 0.0;
	r.p.pos_x = 3.5;
	r.p.pos_y = 3.5;
	r.p.plane_x = -r.p.dir_y;
	r.p.plane_y = r.p.dir_x;
	x = 0;
	y = 0;
	(void)argc;
	(void)argv;
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
		r.camera_x = 2.0 * x / 800.0 - 1.0;
		r.dir_x = r.p.dir_x + r.p.plane_x * r.camera_x;
		r.dir_y = r.p.dir_y + r.p.plane_y * r.camera_x;
		dda(&r, fake_map);
		draw_simple_wall(&img, x, r.perp, 0xFF0000);
		x++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_key_hook(win_ptr, handle_key, NULL);
	mlx_loop(mlx_ptr);
}

// double		pos_x = 2.5;
// double		pos_y = 2.5;
