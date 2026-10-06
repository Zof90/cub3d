/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:37:49 by schouite          #+#    #+#             */
/*   Updated: 2026/10/06 19:56:26 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	my_mlx_put_to_pixel(t_game *game, int x, int y, int pxl)
{
	char	*dst;

	dst = game->data.addr + ((game->data.line_lenght * y) + (x * game->data.bpp
				/ 8));
	*(unsigned int *)dst = pxl;
}
int	get_texture_pixel(t_game *game, int tex_x, int tex_y, int face)
{
	char *dst;
	int pxl;
	
	printf("face=%d addr=%p tex_x=%d tex_y=%d bpp=%d line=%d\n",
	face,
	(void *)game->texture[face].data.addr,
	tex_x,
	tex_y,
	game->texture[face].data.bpp,
	game->texture[face].data.line_lenght);
	dst = game->texture[face].data.addr + ((game->texture[face].data.line_lenght * tex_y)
			+ (tex_x * game->texture[face].data.bpp / 8));
	pxl = *(unsigned int *)dst;
	printf("1\n");
	return (pxl);
}