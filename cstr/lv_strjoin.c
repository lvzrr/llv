/**
 * lv_strjoin.c
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
 * Function: lv_strjoin
 * --------------------
 * Concatenates two null-terminated strings into a new dynamically allocated string.
 *
 * Parameters:
 * s1 - The first string.
 * s2 - The second string.
 *
 * Returns:
 * A pointer to the newly allocated concatenated string on success.
 * NULL if either input string is NULL or if memory allocation fails.
 *
 * Notes:
 * - The caller is responsible for freeing the allocated memory.
 * - Uses `lv_strlen` to determine lengths and `lv_alloc` and `lv_memcpy`
 * for memory handling and copying.
 */

char	*lv_strjoin(const char *s1, const char *s2)
{
	size_t			l1;
	size_t			l2;
	char			*out;

	if (!s1 || !s2)
		return (NULL);
	l1 = lv_strlen(s1);
	l2 = lv_strlen(s2);
	out = lv_alloc(l1 + l2 + 1);
	if (!out)
		return (NULL);
	lv_memcpy(out, s1, l1);
	lv_memcpy(out + l1, s2, l2);
	out[l1 + l2] = 0;
	return (out);
}
