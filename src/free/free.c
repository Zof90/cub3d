/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 14:51:06 by schouite          #+#    #+#             */
/*   Updated: 2026/10/09 19:43:57 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	free_texture(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture[i].data.img)
		{
			mlx_destroy_image(game->mlx_ptr, game->texture[i].data.img);
			game->texture[i].data.img = NULL;
		}
		i++;
	}
}

int	close_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_texture(game);
	if (game->data.img)
		mlx_destroy_image(game->mlx_ptr, game->data.img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit(0);
	return (0);
}
