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

/*
 * Function: lv_split
 * ------------------
 * Splits a string into an array of substrings based on a delimiter character.
 * Each substring is allocated dynamically and the array is NULL-terminated.
 *
 * Parameters:
 * str - The string to be split.
 * set - The delimiter character to split the string by.
 *
 * Returns:
 * A dynamically allocated array of strings (char**) on success.
 * NULL if the input string is NULL or if memory allocation fails.
 *
 * Notes:
 * - The caller is responsible for freeing the allocated memory for each
 * substring and the array itself.
 * - Helper functions `count_words`, `eat_literal`, and `free_words` are used.
 */

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
	out = (char *)lv_alloc(i + 1);
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
				return (lv_free_array((void ***)&out), 0);
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
	out = (char **)lv_alloc((wc + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	out[wc] = NULL;
	if (!fill_words(str, set, out))
		return (lv_free_array((void ***)&out), NULL);
	return (out);
}
