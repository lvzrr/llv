/**
 * lv_vec_rev.c
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
 * Function: lv_vec_reserve
 * ------------------------
 * Ensures that the vector has enough capacity to hold at least `n` more
 * elements without requiring reallocation. If the current allocated size
 * is already sufficient, it does nothing. Otherwise, it extends the capacity.
 *
 * Parameters:
 * v - A pointer to the `t_vec` structure for which to reserve space.
 * n - The number of additional elements to reserve space for.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - If `v` is NULL, `n` is 0, or `n` is less than or equal to the current
 * `v->alloc_size`, the function does nothing.
 * - It uses `lv_extend_zero` to reallocate the underlying buffer and
 * zero out any newly added space.
 * - The `alloc_size` of the vector is increased by `n` after successful reservation.
 * The `size` (number of actual elements) remains unchanged.
 */

void	lv_vec_rev(t_vec *v)
{
	size_t	half;
	size_t	i;

	if (!v || v->size < 2)
		return ;
	half = v->size / 2;
	i = 0;
	while (i < half)
	{
		lv_memswap(
			(t_u8 *)v->data + (v->sizeof_type * i),
			(t_u8 *)v->data + (v->sizeof_type * (v->size - i - 1)),
			v->sizeof_type);
		i++;
	}
}
