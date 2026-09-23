/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:19:31 by schouite          #+#    #+#             */
/*   Updated: 2026/09/23 19:59:47 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// typedef struct s_game
// {
// 	char		**map;
// 	int			map_width;
// 	int			map_height;
// 	t_player	player;
// }				t_game;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	double		delta_x;
	double		delta_y;
	double		side_x;
	double		side_y;
	double		perp;
	double		camera_x;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	t_player	p;
}				t_ray;
#endif