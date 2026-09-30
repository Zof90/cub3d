/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julesmar <julesmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 17:12:18 by julesmar          #+#    #+#             */
/*   Updated: 2026/09/30 17:29:14 by julesmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "libft.h"
#include <stdlib.h>

int	parse_error(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

int	is_blank(char *line)
{
	while (*line == ' ')
		line++;
	return (!*line);
}

int	has_extension(char *path, char *ext)
{
	char	*name;
	size_t	len;
	size_t	ext_len;

	name = ft_strrchr(path, '/');
	if (name)
		name++;
	else
		name = path;
	len = ft_strlen(name);
	ext_len = ft_strlen(ext);
	if (len <= ext_len)
		return (0);
	return (!ft_strncmp(name + len - ext_len, ext, ext_len + 1));
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(game->tex[i]);
		game->tex[i] = NULL;
		i++;
	}
	free_tab(game->map);
	game->map = NULL;
}
