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

/*
 * Function: lv_strtrim
 * --------------------
 * Creates a new string by removing all characters specified in `set`
 * from the beginning and end of the input `str`.
 *
 * Parameters:
 * str - The string to be trimmed.
 * set - The set of characters to trim from the beginning and end of `str`.
 *
 * Returns:
 * A pointer to the newly allocated trimmed string on success.
 * NULL if the input string is NULL or if memory allocation fails.
 *
 * Notes:
 * - The caller is responsible for freeing the allocated memory.
 * - If `str` is empty or only contains characters from `set`, an empty string is returned.
 * - If `set` is empty, a duplicate of `str` is returned.
 */

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

char *lv_strtrim(const char *str, const char *set)
{
    size_t b;
    size_t e;
    size_t trimmed_len;
    char   *out;
    if (!str)
        return (NULL);
    if (!set || !set[0] || !str[0])
        return (lv_strdup(str));
    b = 0;
    e = lv_strlen(str) - 1;
    while (str[b] && in_set(str[b], set) >= 0)
        b++;
    while (e >= b && in_set(str[e], set) >= 0)
        e--;
    if (b > e)
        trimmed_len = 0;
    else
        trimmed_len = e - b + 1;
    out = lv_alloc(trimmed_len + 1);
    if (!out)
        return (NULL);
    lv_memcpy(out, str + b, trimmed_len);
    out[trimmed_len] = '\0';
    return (out);
}
