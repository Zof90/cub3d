/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:17:40 by schouite          #+#    #+#             */
/*   Updated: 2026/09/30 19:57:13 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
// #include "mlx.h"
// #include <math.h>
#include <stdbool.h>

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;
	// if (argc != 2)
	// 	return (parse_error("Usage: ./cub3D <scene.cub>"));
	// if (parse_file(argv[1], &game))
	// 	return (1);
	rendering(&game);
}
