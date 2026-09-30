/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:37:49 by schouite          #+#    #+#             */
/*   Updated: 2026/09/30 17:38:40 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	my_mlx_put_to_pixel(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + ((img->line_lenght * y) + (x * img->bpp / 8));
	*(unsigned int *)dst = color;
}