/**
 * lv_tstr_pop.c
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
 * Function: lv_tstr_pop
 * ---------------------
 * Removes the last character from a `t_string` object, effectively
 * shortening the string by one character. The removed character is returned.
 *
 * Parameters:
 * str - A pointer to the `t_string` object from which to pop a character.
 *
 * Returns:
 * The character that was removed from the end of the string, or 0 (null character)
 * if `str` is NULL, `str->data` is NULL, or the string is empty.
 *
 * Notes:
 * - The function retrieves the last character, then sets the new last character
 * (which was previously the second to last) to null (`\0`) to maintain null-termination,
 * and decrements `str->len`.
 * - The allocated capacity (`str->alloc_size`) remains unchanged.
 */

char	lv_tstr_pop(t_string *str)
{
	char	o;

	if (!str || !str->data || !str->len)
		return (0);
	o = lv_tstr_borrow(str)[str->len - 1];
	str->data[str->len - 1] = 0;
	str->len--;
	return (o);
}
