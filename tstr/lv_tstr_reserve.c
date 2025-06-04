/**
 * lv_tstr_reserve.c
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
 * Function: lv_tstr_reserve
 * -------------------------
 * Ensures that a `t_string` object has enough capacity to hold at least
 * `n` additional characters without requiring reallocation. If the current
 * allocated size is already sufficient, it does nothing. Otherwise, it
 * extends the capacity.
 *
 * Parameters:
 * str - A pointer to the `t_string` object for which to reserve space.
 * n   - The number of additional characters to reserve space for. This
 * includes the space for a potential null terminator if it's part of `n`.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - If `str`, `str->data` is NULL, or `n` is 0, the function does nothing.
 * - If the current `alloc_size` is already greater than or equal to
 * `str->len + n`, no action is taken.
 * - It uses `lv_extend_zero` to reallocate the underlying buffer and
 * zero out any newly added space.
 * - The `alloc_size` of the string is increased by `n` after successful reservation.
 * The `len` (actual string length) remains unchanged.
 */

void	lv_tstr_reserve(t_string *str, size_t n)
{
	char	*new;

	if (!str || !str->data || n == 0)
		return ;
	if (str->alloc_size >= str->len + n)
		return ;
	new = lv_extend_zero(str->data, str->alloc_size, n);
	if (!new)
		return ;
	str->data = new;
	str->alloc_size += n;
}
