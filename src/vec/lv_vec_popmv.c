/**
 * lv_vec_popmv.c
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
 * Function: lv_vec_popmv
 * ----------------------
 * Copies the last element from the vector into `dst`, then removes
 * that element from the vector and zeroes out its memory. The vector's
 * size is decremented. This is a "pop and move" operation.
 *
 * Parameters:
 * dst - A pointer to the destination memory area where the popped element will be copied.
 * v   - A pointer to the `t_vec` structure from which to pop an element.
 *
 * Returns:
 * 1 on success, 0 if `dst`, `v` is NULL, the vector is not allocated, or the vector is empty.
 *
 * Notes:
 * - This function is `inline` for performance.
 * - It uses `lv_vec_peek_last` to get the last element's address and
 * `lv_memtake` to copy it to `dst` and then zero out the source.
 */

inline t_u8	lv_vec_popmv(void *__restrict__ dst,
	t_vec *__restrict__ v)
{
	if (!dst || !v || !v->alloc_size || !v->size)
		return (0);
	lv_memtake(dst, lv_vec_peek_last(v), v->sizeof_type);
	v->size--;
	return (1);
}
