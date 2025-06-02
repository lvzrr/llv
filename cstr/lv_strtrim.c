/**
 * lv_strtrim.c
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

static int	in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*lv_strtrim(const char *str, const char *set)
{
	size_t			b;
	size_t			e;
	size_t			i;
	char			*out;

	if (!str)
		return (NULL);
	if (!set || !set[0] || !str[0])
		return (lv_strdup(str));
	i = 0;
	b = 0;
	e = lv_strlen(str) - 1;
	while (in_set(str[b], set) >= 0)
		b++;
	while (e > b && in_set(str[e], set) >= 0)
		e--;
	out = lv_alloc((e - b) + 2);
	if (!out)
		return (NULL);
	while (b <= e)
		out[i++] = str[b++];
	out[i] = 0;
	return (out);
}
