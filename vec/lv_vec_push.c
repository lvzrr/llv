/**
 * lv_vec_push.c
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
 * Function: lv_vec_push
 * ---------------------
 * Appends `len` new elements from `data` to the end of the vector `vec`.
 * If the vector's current capacity is insufficient, it reallocates
 * the underlying buffer to accommodate the new elements.
 *
 * Parameters:
 * vec  - A pointer to the `t_vec` structure to which elements will be pushed.
 * data - A pointer to the data containing the elements to append.
 * len  - The number of elements to append.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - If `vec` or `data` is NULL, the function does nothing.
 * - If `vec->size + len` exceeds `vec->alloc_size`, the vector's capacity
 * is expanded by doubling its current `alloc_size` or making it just large
 * enough to hold the new elements, whichever is greater. New allocated
 * memory is zeroed out.
 * - It uses `lv_extend_zero` for reallocation and `lv_memcpy` to copy
 * the new data.
 * - The `size` of the vector is incremented by `len` after successful push.
 */

void	lv_vec_push(t_vec *vec, void *data, size_t len)
{
	void	*tmp;
	size_t	new_alloc;

	if (!vec || !data)
		return ;
	if (vec->size + len > vec->alloc_size)
	{
		new_alloc = LV_MAX(vec->alloc_size * 2, vec->size + len);
		tmp = lv_extend_zero(vec->data,
				vec->alloc_size * vec->sizeof_type,
				(new_alloc - vec->alloc_size) * vec->sizeof_type);
		if (!tmp)
			return ;
		vec->data = tmp;
		vec->alloc_size = new_alloc;
	}
	lv_memcpy(((t_u8 *)(vec->data) + (vec->size * vec->sizeof_type)),
		data, len * vec->sizeof_type);
	vec->size += len;
}
