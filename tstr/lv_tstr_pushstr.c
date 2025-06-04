/**
 * lv_tstr_pushstr.c
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
 * Function: lv_tstr_pushstr
 * -------------------------
 * Appends a null-terminated C-style string (`s`) to the end of a `t_string` object (`str`).
 * If the current capacity is insufficient, it reallocates the underlying buffer.
 *
 * Parameters:
 * str - A pointer to the `t_string` object to which the string will be appended.
 * s   - A constant pointer to the null-terminated C-style string to append.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - If `str` or `s` is NULL, the function does nothing.
 * - It calculates the total length needed for the appended string plus null terminator.
 * - If `needed` length exceeds `str->alloc_size`, the capacity is expanded.
 * The new allocation size is `needed` itself, ensuring just enough space for the current content.
 * - It uses `lv_extend_zero` for reallocation and the internal `_append` helper
 * for copying the string data.
 * - The `len` of the `t_string` is updated after successful append.
 */

void	lv_tstr_pushstr(t_string *str, const char *s)
{
	size_t	len;
	size_t	needed;
	char	*new_data;

	if (!str || !s)
		return ;
	len = lv_strlen(s);
	needed = str->len + len + 1;
	if (needed > str->alloc_size)
	{
		new_data = lv_extend_zero(str->data, str->alloc_size,
				(needed - str->alloc_size) * 2);
		if (!new_data)
			return ;
		str->data = new_data;
		str->alloc_size = needed;
	}
	lv_memmove(str->data, s, str->len);
	str->data[str->len] = 0;
	str->len += len;
}
