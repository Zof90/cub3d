/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:32:21 by schouite          #+#    #+#             */
/*   Updated: 2026/10/06 20:14:04 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx.h"
#include "stdbool.h"

int	init_one_texture(t_game *game, int tex)
{
	game->texture[tex].data.img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->tex[tex], &game->texture[tex].width,
			&game->texture[tex].height);
	if (!game->texture[tex].data.img)
		return (0);
	game->texture[tex].data.addr = mlx_get_data_addr(game->texture[tex].data.img,
			&game->texture[tex].data.bpp, &game->texture[tex].data.line_lenght,
			&game->texture[tex].data.endian);
	if (!game->texture[tex].data.addr)
		return (0);
	return (1);
}
int	init_texture(t_game *game)
{
	int		i;
	bool	flag;

	i = 0;
	while (i < 4)
	{
		flag = init_one_texture(game, i);
		if (!flag)
			return (0);
		i++;
	}
	return (1);
}
int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (0);
	game->win_ptr = mlx_new_window(game->mlx_ptr, 800, 600, "cub3D");
	if (!game->win_ptr)
		return (0);
	game->data.img = mlx_new_image(game->mlx_ptr, 800, 600);
	if (!game->data.img)
		return (0);
	game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bpp,
			&game->data.line_lenght, &game->data.endian);
	return (1);
}

// game->texture[TEX_SO].data.img = mlx_xpm_file_to_image(mlx_ptr,
// 		game->tex[TEX_SO], &game->texture[TEX_SO].width,
// 		&game->texture[TEX_SO].height);
// if (!game->texture[TEX_SO].data.img)
// 	return (0);
// game->texture[TEX_SO].data.addr = mlx_get_data_addr(game->texture[TEX_SO].data.img,
// 		&game->texture[TEX_SO].data.bpp,
// 		&game->texture[TEX_SO].data.line_lenght,
// 		&game->texture[TEX_SO].data.endian);
// if (!game->texture[TEX_SO].data.addr)
// 	return (0);
// game->texture[TEX_WE].data.img = mlx_xpm_file_to_image(mlx_ptr,
// 		game->tex[TEX_WE], &game->texture[TEX_WE].width,
// 		&game->texture[TEX_WE].height);
// if (!game->texture[TEX_WE].data.img)
// 	return (0);
// game->texture[TEX_WE].data.addr = mlx_get_data_addr(game->texture[TEX_WE].data.img,
// 		&game->texture[TEX_WE].data.bpp,
// 		&game->texture[TEX_WE].data.line_lenght,
// 		&game->texture[TEX_WE].data.endian);
// if (!game->texture[TEX_WE].data.addr)
// 	return (0);
// game->texture[TEX_EA].data.img = mlx_xpm_file_to_image(mlx_ptr,
// 		game->tex[TEX_EA], &game->texture[TEX_EA].width,
// 		&game->texture[TEX_EA].height);
// if (!game->texture[TEX_EA].data.img)
// 	return (0);
// game->texture[TEX_EA].data.addr = mlx_get_data_addr(game->texture[TEX_EA].data.img,
// 		&game->texture[TEX_EA].data.bpp,
// 		&game->texture[TEX_EA].data.line_lenght,
// 		&game->texture[TEX_EA].data.endian);
// if (!game->texture[TEX_EA].data.addr)
// 	return (0);