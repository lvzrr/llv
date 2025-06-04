/**
 * lv_tstr_clear.c
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
 * Function: lv_tstr_clear
 * -----------------------
 * Clears the contents of a `t_string` object.
 * This sets the string's length to zero and fills the currently
 * used portion of its internal data buffer with null bytes.
 * The allocated memory capacity remains unchanged.
 *
 * Parameters:
 * s - A pointer to the `t_string` object to be cleared.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - If `s` is NULL or `s->data` is NULL (meaning the string is not initialized
 * or has no allocated memory), the function performs no action.
 * - It uses `lv_memset` to efficiently zero out the characters.
 * - The `alloc_size` of the string is preserved, allowing for new content
 * to be added without immediate reallocation.
 */

void	lv_tstr_clear(t_string *s)
{
	if (!s || !s->data)
		return ;
	lv_memset(s->data, 0, s->len);
	s->len = 0;
}
