/**
 * get_next_line.c
 *
 * Copyright (C) 2025 lvzrr <lvzrr@proton.me>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version
 * 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General
 * Public License along with this program. If not, see
 * <https://www.gnu.org/licenses/>.
 */

#include "liblv.h"

static void	*free_buf(char **ptr)
{
	if (!ptr || !*ptr)
		return (*ptr = NULL, NULL);
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static char	*manage_buffer(char *buffer)
{
	char	*brkpnt;
	char	*realloc;
	size_t	newlpos;

	brkpnt = lv_strchr(buffer, '\n');
	if (!brkpnt)
	{
		realloc = NULL;
		return (free_buf(&buffer));
	}
	else
		newlpos = (brkpnt - buffer) + 1;
	if (!buffer[newlpos])
		return (free_buf(&buffer));
	realloc = lv_substr(buffer, newlpos, lv_strlen(buffer) - newlpos);
	if (!realloc && buffer)
		return (free_buf(&buffer));
	free_buf(&buffer);
	return (realloc);
}

static char	*getl(char *buffer)
{
	char	*line;
	char	*p;
	size_t	l;

	if (!buffer)
		return (NULL);
	p = lv_strchr(buffer, '\n');
	if (p)
		l = (p - buffer) + 1;
	else
		l = lv_strlen(buffer);
	line = lv_substr(buffer, 0, l);
	if (!line)
		return (NULL);
	return (line);
}

static char	*read_buffer(int fd, char *buffer)
{
	char	*tmp;
	char	*joined;
	int		bread;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (free_buf(&buffer));
	bread = 1;
	while (bread > 0 && !lv_strchr(buffer, '\n'))
	{
		bread = read(fd, tmp, BUFFER_SIZE);
		if (bread > 0)
		{
			tmp[bread] = '\0';
			joined = lv_strjoin(buffer, tmp);
			if (!joined)
				return (free_buf(&tmp), free_buf(&buffer));
			free_buf(&buffer);
			buffer = joined;
		}
	}
	free_buf(&tmp);
	if (bread == -1)
		return (free_buf(&buffer));
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = lv_strdup("");
		if (!buffer)
			return (NULL);
	}
	if (!lv_strchr(buffer, '\n'))
	{
		buffer = read_buffer(fd, buffer);
		if (!buffer || buffer[0] == '\0')
			return (free_buf(&buffer));
	}
	line = getl(buffer);
	if (!line && buffer)
		return (free_buf(&buffer));
	buffer = manage_buffer(buffer);
	return (line);
}
