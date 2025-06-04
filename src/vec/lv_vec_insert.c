/**
 * lv_vec_insert.c
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
 * Function: lv_vec_insert
 * -----------------------
 * Inserts `len` new elements from `data` into the vector `v` at the
 * specified `index`. This operation shifts existing elements to the right
 * to accommodate the new elements.
 *
 * Parameters:
 * v     - A pointer to the `t_vec` structure where elements will be inserted.
 * index - The zero-based index at which to insert the new elements.
 * data  - A pointer to the data containing the elements to insert.
 * len   - The number of elements to insert.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - If `v`, `data` is NULL, `len` is 0, or `index` is out of bounds
 * (`index > v->size`), the function does nothing.
 * - If the vector's current capacity is insufficient (`v->size + len > v->alloc_size`),
 * it reallocates the underlying buffer, doubling its size or making it just
 * large enough to hold the new elements, whichever is greater. New allocated
 * memory is zeroed out.
 * - It uses `lv_memmove` to shift existing data and `lv_memcpy` to copy
 * the new data into the insertion point.
 * - The `size` of the vector is incremented by `len` after successful insertion.
 */

void	lv_vec_insert(t_vec *v, size_t index, void *data, size_t len)
{
	void	*new;
	size_t	new_alloc;

	if (!v || !data || len == 0 || index > v->size)
		return ;
	if (v->alloc_size < v->size + len)
	{
		new_alloc = LV_MAX(v->alloc_size * 2, v->size + len);
		new = lv_extend_zero(v->data, v->alloc_size * v->sizeof_type,
				(new_alloc - v->alloc_size) * v->sizeof_type);
		if (!new)
			return ;
		v->data = new;
		v->alloc_size = new_alloc;
	}
	lv_memmove((t_u8 *)v->data + (index + len) * v->sizeof_type,
		(t_u8 *)v->data + index * v->sizeof_type,
		(v->size - index) * v->sizeof_type);
	lv_memcpy((t_u8 *)v->data + index * v->sizeof_type,
		data, len * v->sizeof_type);
	v->size += len;
}
