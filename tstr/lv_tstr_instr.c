/**
 * lv_tstr_instr.c
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
#include "tstr.h"

/*
 * Function: lv_find
 * -----------------
 * A static helper function to find the first occurrence of a `needle` string
 * within a `haystack` string, considering a maximum search length `n`.
 *
 * Parameters:
 * haystack - The string to search within.
 * needle   - The string to search for.
 * n        - The maximum number of bytes to search in `haystack`.
 * l        - The length of the `needle` string (passed as `l` for efficiency).
 *
 * Returns:
 * The zero-based index of the first occurrence of `needle` in `haystack`,
 * or -1 if `needle` is not found within `n` bytes.
 * Returns 0 if `needle` is an empty string.
 * Returns -1 if `haystack` is an empty string and `needle` is not empty.
 *
 * Notes:
 * - This function is designed to be used internally by `lv_tstr_instr`.
 * - It checks for initial characters and then uses `lv_strncmp` for full substring comparison.
 */

static ssize_t	lv_find(const char *haystack, const char *needle, size_t n,
							size_t l)
{
	size_t	i;

	i = 0;
	l = 0;
	if (!*needle)
		return (0);
	if (!*haystack)
		return (-1);
	while (haystack[i] && (i + l) <= n)
	{
		if (haystack[i] == needle[0] && !lv_strncmp(&(haystack[i]), needle, l))
			return ((ssize_t) i);
		i++;
	}
	return (-1);
}

/*
 * Function: lv_tstr_instr
 * -----------------------
 * Searches for the first occurrence of a null-terminated C-style string (`n`)
 * within a `t_string` object (`h`).
 *
 * Parameters:
 * h - A constant pointer to the `t_string` object to search within.
 * n - A constant pointer to the null-terminated C-style string to search for.
 *
 * Returns:
 * The zero-based index of the first occurrence of `n` in `h`,
 * or -1 if `h`, `h->data`, or `n` is NULL, or if `n` is not found.
 *
 * Notes:
 * - It calculates the length of the `needle` string (`n`) once for efficiency.
 * - It delegates the actual search logic to the internal `lv_find` helper function.
 */

ssize_t	lv_tstr_instr(const t_string *h, const char *n)
{
	size_t	l;

	if (!h ||!h->data || !n)
		return (-1);
	l = lv_strlen(n);
	return (lv_find(lv_tstr_borrow(h), n, h->len, l));
}
