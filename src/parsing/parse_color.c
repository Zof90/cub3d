/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julesmar <julesmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 11:34:19 by julesmar          #+#    #+#             */
/*   Updated: 2026/09/30 17:27:45 by julesmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "libft.h"

static int	read_channel(char **s)
{
	int	value;

	value = 0;
	while (**s == ' ')
		(*s)++;
	if (!ft_isdigit(**s))
		return (-1);
	while (ft_isdigit(**s))
	{
		value = value * 10 + (**s - '0');
		if (value > 255)
			return (-1);
		(*s)++;
	}
	while (**s == ' ')
		(*s)++;
	return (value);
}

int	parse_color(char *s, int *dst)
{
	int	rgb[3];
	int	i;

	if (*dst != -1)
		return (parse_error("Duplicate color element"));
	i = 0;
	while (i < 3)
	{
		rgb[i] = read_channel(&s);
		if (rgb[i] < 0 || (i < 2 && *s != ',') || (i == 2 && *s))
			return (parse_error("Color must be R,G,B with values in [0,255]"));
		s++;
		i++;
	}
	*dst = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (0);
}
