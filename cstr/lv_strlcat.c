/**
 * lv_strlcat.c
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
 * Function: lv_strlcat
 * --------------------
 * Concatenates a null-terminated source string to a null-terminated
 * destination buffer, ensuring null termination and preventing buffer overflow.
 *
 * Parameters:
 * dest - The destination buffer.
 * src  - The source string to append.
 * n    - The total size of the destination buffer (including null terminator).
 *
 * Returns:
 * The total length of the string that would have been created if there
 * was enough room (strlen(src) + strlen(initial dest)).
 *
 * Notes:
 * - Appends at most `n - strlen(dest) - 1` bytes from `src`.
 * - Always null-terminates the result if `n` is greater than 0.
 */

size_t	lv_strlcat(char *dest, const char *src, size_t n)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = lv_strlen(src);
	dstlen = lv_strlen(dest);
	if (n <= dstlen)
		return (srclen + n);
	i = 0;
	while (dstlen + i < n - 1 && src[i])
	{
		dest[dstlen + i] = src[i];
		i++;
	}
	dest[dstlen + i] = 0;
	return (srclen + dstlen);
}
