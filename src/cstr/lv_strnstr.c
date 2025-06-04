/**
 * lv_strnstr.c
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
 * Function: lv_strnstr
 * --------------------
 * Locates the first occurrence of a null-terminated needle string within
 * a null-terminated haystack string, examining at most `n` characters.
 *
 * Parameters:
 * haystack - The string to be searched.
 * needle   - The string to search for.
 * n        - The maximum number of characters to search within `haystack`.
 *
 * Returns:
 * A pointer to the first character of the first occurrence of `needle` in
 * `haystack` within the first `n` characters.
 * If `needle` is an empty string, `haystack` is returned.
 * NULL if `needle` is not found within the specified length, or if
 * `haystack` is an empty string and `needle` is not empty.
 *
 * Notes:
 * - If `n` is 0, the function will not find any matches unless `needle` is empty.
 * - Uses `lv_strlen` and `lv_strncmp`.
 */

char	*lv_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	l;

	if (!needle || !*needle)
		return ((char *)haystack);
	if (!haystack || !*haystack)
		return (NULL);
	i = 0;
	l = lv_strlen(needle);
	if (l > n)
		return (NULL);
	while (haystack[i] && (i + l) <= n)
	{
		if (!lv_strncmp(&(haystack[i]), needle, l))
			return ((char *)(&(haystack[i])));
		i++;
	}
	return ((void *) 0);
}
