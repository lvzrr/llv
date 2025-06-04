/**
 * lv_tstr_borrow.c
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
 * Function: lv_tstr_borrow
 * ------------------------
 * Returns a constant pointer to the underlying C-style string data
 * of a `t_string` object. This allows direct access to the string's
 * contents without copying.
 *
 * Parameters:
 * str - A constant pointer to the `t_string` object.
 *
 * Returns:
 * A constant `char` pointer to the internal string data.
 *
 * Notes:
 * - The caller should not modify the returned pointer's contents as
 * it points directly to the `t_string`'s internal buffer.
 * - The returned pointer remains valid only as long as the `t_string`
 * object itself is not modified (e.g., through reallocation or content changes).
 */

const char	*lv_tstr_borrow(const t_string *str)
{
	return (str->data);
}
