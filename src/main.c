/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:17:40 by schouite          #+#    #+#             */
/*   Updated: 2026/09/30 18:21:51 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
// #include "mlx.h"
// #include <math.h>
#include <stdbool.h>



int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	rendering();
		t_game	game;

	if (argc != 2)
		return (parse_error("Usage: ./cub3D <scene.cub>"));
	if (parse_file(argv[1], &game))
		return (1);
}

// double		pos_x = 2.5;
// double		pos_y = 2.5;
