/**
 * lv_tstr_from_cstr.c
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

#include "llv.h"

/*
 * Function: lv_tstr_from_cstr
 * ---------------------------
 * Creates and initializes a new `t_string` object from a null-terminated
 * C-style string (`const char *`). It allocates memory and copies the
 * content of the input C-string.
 *
 * Parameters:
 * str - A constant pointer to the null-terminated C-style string to convert.
 *
 * Returns:
 * A new `t_string` object containing the copied string data.
 * If `str` is NULL, it returns an empty `t_string` with a single null byte allocated.
 * If memory allocation fails, it returns an empty `t_string` with `data` set to NULL.
 *
 * Notes:
 * - It calculates the length of the input string using `lv_strlen`.
 * - It allocates `len + 1` bytes to accommodate the string content plus the null terminator.
 * - The allocated memory is zeroed out using `lv_memset` before copying the string.
 * - It uses `lv_alloc` for initial allocation and `lv_memcpy` for copying the data.
 */

t_string	lv_tstr_from_cstr(const char *str)
{
	t_string	out;

	if (!str)
	{
		out.len = 0;
		out.alloc_size = 1;
		out.data = lv_alloc(1);
		lv_memset(out.data, 0, 1);
	}
	else
	{
		out.len = lv_strlen(str);
		out.alloc_size = out.len + 1;
		out.data = lv_alloc(out.alloc_size);
		lv_memset(out.data, 0, out.alloc_size);
		if (out.data)
			lv_memcpy(out.data, str, out.len);
	}
	return (out);
}
