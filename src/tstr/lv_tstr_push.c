/**
 * lv_tstr_push.c
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
 * Function: lv_tstr_push
 * ----------------------
 * Appends a single character (`c`) to the end of a `t_string` object.
 * If the string's current capacity is insufficient, it reallocates
 * the underlying buffer to accommodate the new character.
 *
 * Parameters:
 * str - A pointer to the `t_string` object to which the character will be pushed.
 * c   - The character to append.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - If `str` is NULL, the function does nothing.
 * - If the current `alloc_size` is not enough to hold the new character
 * and the null terminator (`str->len + 1 < str->alloc_size`), the data
 * is directly appended.
 * - Otherwise, the capacity is doubled using `lv_extend_zero` to make space.
 * - The new character is placed at `str->data[str->len]`, `str->len` is
 * incremented, and a null terminator is placed at the new end.
 */

void	lv_tstr_push(t_string *str, char c)
{
	if (!str)
		return ;
	if (str->len + 1 < str->alloc_size)
	{
		str->data[str->len++] = c;
		str->data[str->len] = 0;
		return ;
	}
	str->data = lv_extend_zero(str->data, str->alloc_size, str->alloc_size * 2);
	str->alloc_size *= 2;
	if (!str->data)
		return ;
	str->data[str->len++] = c;
	str->data[str->len] = 0;
}
