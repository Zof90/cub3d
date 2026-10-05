/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:32:21 by schouite          #+#    #+#             */
/*   Updated: 2026/10/05 22:11:45 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx.h"

int	int_texture(t_game *game, void *mlx_ptr)
{
	game->texture[TEX_NO].data.img = mlx_xpm_file_to_image(mlx_ptr,
			game->tex[TEX_NO], &game->texture[TEX_NO].width,
			&game->texture[TEX_NO].height);
	if (!game->texture[TEX_NO].data.img)
		return (0);
	game->texture[TEX_NO].data.addr = mlx_get_data_addr(game->texture[TEX_NO].data.img,
			&game->texture[TEX_NO].data.bpp,
			&game->texture[TEX_NO].data.line_lenght,
			&game->texture[TEX_NO].data.endian);
	if (!game->texture[TEX_NO].data.addr)
		return (0);
	game->texture[TEX_SO].data.img = mlx_xpm_file_to_image(mlx_ptr,
			game->tex[TEX_SO], &game->texture[TEX_SO].width,
			&game->texture[TEX_SO].height);
	if (!game->texture[TEX_SO].data.img)
		return (0);
	game->texture[TEX_SO].data.addr = mlx_get_data_addr(game->texture[TEX_SO].data.img,
			&game->texture[TEX_SO].data.bpp,
			&game->texture[TEX_SO].data.line_lenght,
			&game->texture[TEX_SO].data.endian);
	if (!game->texture[TEX_SO].data.addr)
		return (0);
	game->texture[TEX_WE].data.img = mlx_xpm_file_to_image(mlx_ptr,
			game->tex[TEX_WE], &game->texture[TEX_WE].width,
			&game->texture[TEX_WE].height);
	if (!game->texture[TEX_WE].data.img)
		return (0);
	game->texture[TEX_WE].data.addr = mlx_get_data_addr(game->texture[TEX_WE].data.img,
			&game->texture[TEX_WE].data.bpp,
			&game->texture[TEX_WE].data.line_lenght,
			&game->texture[TEX_WE].data.endian);
	if (!game->texture[TEX_WE].data.addr)
		return (0);
	game->texture[TEX_EA].data.img = mlx_xpm_file_to_image(mlx_ptr,
			game->tex[TEX_EA], &game->texture[TEX_EA].width,
			&game->texture[TEX_EA].height);
	if (!game->texture[TEX_EA].data.img)
		return (0);
	game->texture[TEX_EA].data.addr = mlx_get_data_addr(game->texture[TEX_EA].data.img,
			&game->texture[TEX_EA].data.bpp,
			&game->texture[TEX_EA].data.line_lenght,
			&game->texture[TEX_EA].data.endian);
	if (!game->texture[TEX_EA].data.addr)
		return (0);
	return (1);
}
int	init_mlx(t_data *data, void **mlx_ptr, void **win_ptr)
{
	*mlx_ptr = mlx_init();
	if (!*mlx_ptr)
		return (0);
	*win_ptr = mlx_new_window(*mlx_ptr, 800, 600, "cub3D");
	if (!*win_ptr)
		return (0);
	data->img = mlx_new_image(*mlx_ptr, 800, 600);
	if (!data->img)
		return (0);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_lenght,
			&data->endian);
	return (1);
}
