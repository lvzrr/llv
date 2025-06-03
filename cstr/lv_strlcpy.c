/**
* lv_strlcpy.c
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
 * Function: lv_strlcpy
 * --------------------
 * Copies a null-terminated source string to a destination buffer,
 * ensuring null termination and preventing buffer overflow.
 *
 * Parameters:
 * dest - The destination buffer.
 * src  - The source string to copy.
 * n    - The total size of the destination buffer (including null terminator).
 *
 * Returns:
 * The total length of the source string (strlen(src)).
 *
 * Notes:
 * - Copies at most `n - 1` bytes from `src` to `dest`.
 * - Always null-terminates the result if `n` is greater than 0.
 * - If `dest` is NULL or `n` is 0, it returns the length of `src`
 * without performing any copy.
 */

size_t lv_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	src_len;
	size_t	bytes_to_copy;

	if (!src)
		return 0;
	src_len = lv_strlen(src);
	if (n == 0 || !dest)
		return src_len;
	if (src_len < (n - 1))
		bytes_to_copy = src_len;
	else
		bytes_to_copy = n - 1;
	lv_memcpy(dest, src, bytes_to_copy);
	dest[bytes_to_copy] = '\0';
	return (src_len);
}
