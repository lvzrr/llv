/**
 * lv_strchr.c
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
 * Function: lv_strchr
 * --------------------
 * Locates the first occurrence of a character in a string.
 *
 * Parameters:
 * s - The string to be searched.
 * c - The character to search for (an int, but treated as char).
 *
 * Returns:
 * A pointer to the first occurrence of `c` in `s`.
 * NULL if the character is not found.
 *
 * Notes:
 * - This function is optimized to search for the character `c` in blocks of `t_u64` (unsigned 64-bit integers)
 * after handling the initial bytes to align the string pointer.
 * - It uses `__hasz64` to check for a null byte within a 64-bit word and `_lookup_u64`
 * to find the character `c` within a 64-bit word.
 * - The `cstr.h` header is presumed to define `t_u64`, `t_uptr`, `__hasz64`, and `_populate`.
 */

char	*lv_strchr(const char *s, int c)
{
	t_u64	*w;
	int		idx;
	char	*s2;

	if (!s)
		return (NULL);
	s2 = (char *)s;
	while (((t_uptr)s2) % sizeof(t_u64) != 0
		&& *s2 != (char)c && *s2 != '\0')
		s2++;
	if (*s2 == c)
		return (s2);
	w = (t_u64 *)s2;
	while (!__hasz64(w[0]))
	{
		idx = _lookup_u64(w[0], __populate((t_u8)c));
		if (idx != -1)
			return (((char *)w) + idx);
		w++;
	}
	return (NULL);
}
