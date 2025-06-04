/**
 * lv_tstr_trim.c
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

#include "tstr.h"

/*
 * Function: in_set
 * ----------------
 * A static helper function to check if a given character `c` is present
 * within a null-terminated set of characters `set`.
 *
 * Parameters:
 * c   - The character to check.
 * set - A constant pointer to a null-terminated string representing the set of characters.
 *
 * Returns:
 * 1 if `c` is found in `set`, 0 otherwise.
 *
 * Notes:
 * - This function is designed to be used internally by `lv_tstr_trim`.
 */

static int	in_set(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
 * Function: lv_tstr_trim
 * ----------------------
 * Removes leading and trailing characters from a `t_string` object (`str`)
 * that are present in a specified `set` of characters. This modifies the
 * string in-place.
 *
 * Parameters:
 * str - A pointer to the `t_string` object to be trimmed.
 * set - A constant pointer to a null-terminated string containing the
 * characters to trim (e.g., " \t\n" for whitespace).
 *
 * Returns:
 * None.
 *
 * Notes:
 * - If `str`, `str->data`, `str->len` is 0, or `set` is NULL, the function does nothing.
 * - It first identifies the `start` and `end` indices of the non-trimmed content.
 * - `lv_memmove` is used to shift the trimmed content to the beginning of the buffer.
 * - Any remaining space in the buffer after trimming is zeroed out using `lv_memset`.
 * - The `len` of the `t_string` is updated to reflect the new length.
 * - The `alloc_size` remains unchanged, but the string's content is effectively
 * shortened and its data shifted.
 */

void	lv_tstr_trim(t_string *str, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	new_len;

	if (!str || !str->data || !str->len || !set)
		return ;
	start = 0;
	end = str->len;
	while (start < end && in_set(str->data[start], set))
		start++;
	while (end > start && in_set(str->data[end - 1], set))
		end--;
	new_len = end - start;
	lv_memmove(str->data, str->data + start, new_len);
	if (str->alloc_size > new_len)
		lv_memset(str->data + new_len, 0, str->alloc_size - new_len);
	str->len = new_len;
}
