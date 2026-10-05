/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:32:21 by schouite          #+#    #+#             */
/*   Updated: 2026/10/05 21:32:19 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx.h"
int int_texture(t_game *game)
{
	game->tex[0]= 
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
