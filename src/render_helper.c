/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 19:41:42 by schouite          #+#    #+#             */
/*   Updated: 2026/10/06 19:50:21 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_texture_face(t_game *game)
{
	int face;

	if (game->ray.side == 0 && game->ray.step_x > 0)
		face = TEX_WE;
	else if (game->ray.side == 0 && game->ray.step_x < 0)
		face = TEX_EA;
    if (game->ray.side == 1 && game->ray.step_y > 0)
        face = TEX_NO;
    if (game->ray.side == 1 && game->ray.step_y < 0)
        face = TEX_SO;
    return(face);
}