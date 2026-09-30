/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:32:21 by schouite          #+#    #+#             */
/*   Updated: 2026/09/30 17:33:09 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx.h"

int	init_mlx(t_data *img, void **mlx_ptr, void **win_ptr)
{
	*mlx_ptr = mlx_init();
	if (!*mlx_ptr)
		return (0);
	*win_ptr = mlx_new_window(*mlx_ptr, 800, 600, "cub3D");
	if (!*win_ptr)
		return (0);
	img->img = mlx_new_image(*mlx_ptr, 800, 600);
	if (!img->img)
		return (0);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_lenght,
			&img->endian);
	return (1);
}