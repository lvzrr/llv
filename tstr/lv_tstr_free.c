/**
 * lv_tstr_free.c
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
 * Function: lv_tstr_free
 * ----------------------
 * Deallocates the memory associated with a `t_string` object's data
 * and resets its internal state (`len`, `alloc_size`, `data`) to zero.
 * This function should be called when a `t_string` is no longer needed
 * to prevent memory leaks.
 *
 * Parameters:
 * str - A pointer to the `t_string` object to be freed.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - It handles cases where `str->data` might already be NULL.
 * - It uses `lv_free` to deallocate the `data` pointer.
 * - After freeing, `str->data` is set to NULL, and `str->len` and
 * `str->alloc_size` are set to 0.
 */

void	lv_tstr_free(t_string *str)
{
	void	*tmp;

	if (str->data)
	{
		tmp = str->data;
		lv_free(&tmp);
		str->data = NULL;
	}
	str->len = 0;
	str->alloc_size = 0;
}
