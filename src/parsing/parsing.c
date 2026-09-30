/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julesmar <julesmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 11:12:12 by julesmar          #+#    #+#             */
/*   Updated: 2026/09/30 17:26:50 by julesmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->floor = -1;
	game->ceiling = -1;
}

int	parse_file(char *path, t_game *game)
{
	char	*content;
	char	**lines;
	int		start;
	int		ret;

	init_game(game);
	if (!has_extension(path, ".cub"))
		return (parse_error("Scene file must have a .cub extension"));
	content = read_file(path);
	if (!content)
		return (parse_error(strerror(errno)));
	lines = split_lines(content);
	free(content);
	if (!lines)
		return (parse_error("Memory allocation failed"));
	start = parse_elements(lines, game);
	ret = (start < 0 || parse_map(lines + start, game));
	free_tab(lines);
	if (ret)
		free_game(game);
	return (ret);
}
