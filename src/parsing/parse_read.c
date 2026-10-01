/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 11:15:12 by julesmar          #+#    #+#             */
/*   Updated: 2026/09/30 18:33:08 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static char	*join_free(char *content, char *buf)
{
	char	*joined;

	joined = ft_strjoin(content, buf);
	free(content);
	return (joined);
}

static char	*read_fd(int fd)
{
	char	buf[READ_SIZE + 1];
	char	*content;
	ssize_t	n;

	content = ft_strdup("");
	n = 1;
	while (content && n > 0)
	{
		n = read(fd, buf, READ_SIZE);
		if (n > 0)
		{
			buf[n] = '\0';
			content = join_free(content, buf);
		}
	}
	if (n < 0)
	{
		free(content);
		return (NULL);
	}
	return (content);
}

/* Returns NULL with errno set if the file cannot be read. */
char	*read_file(char *path)
{
	char	*content;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = read_fd(fd);
	close(fd);
	return (content);
}

static size_t	count_lines(char *s)
{
	size_t	count;

	count = 1;
	while (*s)
	{
		if (*s == '\n')
			count++;
		s++;
	}
	return (count);
}

char	**split_lines(char *s)
{
	char	**lines;
	size_t	len;
	size_t	i;

	lines = ft_calloc(count_lines(s) + 1, sizeof(char *));
	i = 0;
	while (lines)
	{
		len = 0;
		while (s[len] && s[len] != '\n')
			len++;
		lines[i] = ft_substr(s, 0, len);
		if (!lines[i])
		{
			free_tab(lines);
			return (NULL);
		}
		if (!s[len])
			break ;
		s += len + 1;
		i++;
	}
	return (lines);
}
