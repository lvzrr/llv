/**
 * lv_vec_clear.c
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

#include "vec.h"

/*
 * Function: lv_vec_clear
 * ----------------------
 * Clears the contents of a vector, effectively making its `size` zero,
 * without deallocating the underlying memory. The memory occupied by
 * the current elements is zeroed out.
 *
 * Parameters:
 * vec - A pointer to the `t_vec` structure to be cleared.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - If `vec` or `vec->data` is NULL, the function does nothing.
 * - It uses `lv_memset` to set the existing data to zero.
 * - The allocated memory (`vec->data` and `vec->alloc_size`) remains
 * untouched, allowing for future additions without reallocating immediately.
 */

void	lv_vec_clear(t_vec *vec)
{
	if (!vec || !vec->data)
		return ;
	lv_memset(vec->data, 0, vec->size * vec->sizeof_type);
	vec->size = 0;
}
