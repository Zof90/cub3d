/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 16:33:40 by schouite          #+#    #+#             */
/*   Updated: 2026/09/30 15:26:55 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

static void	dda_int_steps(t_ray *r)
{
	r->map_x = (int)r->p.pos_x;
	r->map_y = (int)r->p.pos_y;
	if (!r->dir_x)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->dir_x);
	if (!r->dir_y)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->dir_y);
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
void	raycast(t_data *img)
{
	t_ray r;
	int x;

	r.p.dir_x = -1.0;
	r.p.dir_y = 0.0;
	r.p.pos_x = 3.5;
	r.p.pos_y = 3.5;
	r.p.plane_x = -r.p.dir_y * 0.66;
	r.p.plane_y = r.p.dir_x * 0.66;
	char *fake_map[] = {"11111111", "10000001", "10100101", "10000001",
		"11111111", NULL};
	x = 0;
	while (x < WIDTH)
	{
		r.camera_x = 2.0 * x / 800.0 - 1.0;
		r.dir_x = r.p.dir_x + r.p.plane_x * r.camera_x;
		r.dir_y = r.p.dir_y + r.p.plane_y * r.camera_x;
		dda(&r, fake_map);
		draw_wall(img, x, r.perp, 0xFF0000);
		x++;
	}
}