/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julesmar <julesmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:20:45 by julesmar          #+#    #+#             */
/*   Updated: 2026/09/30 17:28:04 by julesmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

static int	parse_texture(char *s, char **dst)
{
	int	fd;

	if (*dst)
		return (parse_error("Duplicate texture element"));
	*dst = ft_strtrim(s, " ");
	if (!*dst)
		return (parse_error("Memory allocation failed"));
	if (!has_extension(*dst, ".xpm"))
		return (parse_error("Texture must be a .xpm file"));
	fd = open(*dst, O_RDONLY);
	if (fd < 0)
		return (parse_error("Cannot open texture file"));
	close(fd);
	return (0);
}

static int	parse_element(char *line, t_game *game)
{
	while (*line == ' ')
		line++;
	if (!ft_strncmp(line, "NO ", 3))
		return (parse_texture(line + 3, &game->tex[TEX_NO]));
	if (!ft_strncmp(line, "SO ", 3))
		return (parse_texture(line + 3, &game->tex[TEX_SO]));
	if (!ft_strncmp(line, "WE ", 3))
		return (parse_texture(line + 3, &game->tex[TEX_WE]));
	if (!ft_strncmp(line, "EA ", 3))
		return (parse_texture(line + 3, &game->tex[TEX_EA]));
	if (!ft_strncmp(line, "F ", 2))
		return (parse_color(line + 2, &game->floor));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_color(line + 2, &game->ceiling));
	return (parse_error("Invalid or missing element before the map"));
}

static int	elements_done(t_game *game)
{
	return (game->tex[TEX_NO] && game->tex[TEX_SO] && game->tex[TEX_WE]
		&& game->tex[TEX_EA] && game->floor != -1 && game->ceiling != -1);
}

/* Returns the index of the first line of the map, or -1 on error. */
int	parse_elements(char **lines, t_game *game)
{
	int	i;

	i = 0;
	while (lines[i] && !elements_done(game))
	{
		if (!is_blank(lines[i]) && parse_element(lines[i], game))
			return (-1);
		i++;
	}
	if (!elements_done(game))
	{
		parse_error("Missing texture or color element");
		return (-1);
	}
	while (lines[i] && is_blank(lines[i]))
		i++;
	return (i);
}
