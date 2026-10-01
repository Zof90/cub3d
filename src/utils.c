/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:37:49 by schouite          #+#    #+#             */
/*   Updated: 2026/10/01 16:47:14 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	my_mlx_put_to_pixel(t_game *game, int x, int y, int pxl)
{
	char *dst;

	dst = game->data.addr + ((game->data.line_lenght * y) + (x * game->data.bpp / 8));
	*(unsigned int *)dst = pxl;
}