/**
 * lv_split.c
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

#include "cstr.h"

static unsigned int	count_words(char *str, char set)
{
	unsigned int	iw;
	unsigned int	wc;

	iw = 0;
	wc = 0;
	while (*str)
	{
		if (!iw && *str != set)
		{
			iw = 1;
			wc++;
		}
		if (iw && *str == set)
			iw = 0;
		str++;
	}
	return (wc);
}

static char	*eat_literal(char *str, char set)
{
	int		i;
	char	*out;

	i = 0;
	while (str[i] && str[i] != set)
		i++;
	out = (char *)malloc(i + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != set)
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

static void	free_words(char **out)
{
	int	i;

	i = 0;
	while (out[i])
		free(out[i++]);
	free(out);
}

static int	fill_words(const char *str, char set, char **out)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != set)
		{
			out[j] = eat_literal((char *)str + i, set);
			if (!out[j])
				return (0);
			j++;
			while (str[i] && str[i] != set)
				i++;
			continue ;
		}
		i++;
	}
	return (1);
}

char	**lv_split(const char *str, char set)
{
	char			**out;
	unsigned int	wc;

	if (!str)
		return (NULL);
	wc = count_words((char *)str, set);
	out = (char **)malloc((wc + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	out[wc] = NULL;
	if (!fill_words(str, set, out))
	{
		free_words(out);
		return (NULL);
	}
	return (out);
}
