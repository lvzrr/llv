/**
 * lv_strrchr.c
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
 * Function: lv_strrchr
 * --------------------
 * Locates the last occurrence of a character in a string.
 *
 * Parameters:
 * haystack - The string to be searched.
 * needle   - The character to search for (an int, but treated as char).
 *
 * Returns:
 * A pointer to the last occurrence of `needle` in `haystack`.
 * NULL if the character is not found.
 *
 * Notes:
 * - Searches from the end of the string towards the beginning.
 */

char	*lv_strrchr(const char *haystack, int needle)
{
	size_t	l;

	l = lv_strlen(haystack);
	while (l != 0 && haystack[l] != (char)needle)
		l--;
	if (haystack[l] != (char)needle)
		return (NULL);
	return ((char *)(haystack + l));
}
