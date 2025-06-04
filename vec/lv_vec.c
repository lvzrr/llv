/**
 * lv_vec.c
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
 * Function: lv_vec
 * ----------------
 * Initializes and allocates memory for a new `t_vec` (vector) object.
 * A vector is a dynamic array that can grow or shrink as needed.
 *
 * Parameters:
 * alloc_size  - The initial number of elements to allocate space for.
 * sizeof_type - The size, in bytes, of each element that will be stored in the vector.
 *
 * Returns:
 * A `t_vec` structure initialized with allocated memory and properties.
 * If allocation fails or input parameters are invalid (e.g., zero sizes,
 * or integer overflow during size calculation), it returns an empty `t_vec`
 * with all its members set to 0.
 *
 * Notes:
 * - It performs a check for potential integer overflow when calculating
 * the total memory size (`alloc_size * sizeof_type`).
 * - The `size` member is initialized to 0, indicating an empty vector,
 * while `alloc_size` holds the capacity.
 * - It uses `lv_alloc` for memory allocation.
 */

t_vec	lv_vec(size_t alloc_size, size_t sizeof_type)
{
	t_vec	out;

	if (!alloc_size || !sizeof_type)
		return ((t_vec){0});
	if (SIZE_MAX / alloc_size <= sizeof_type)
		return ((t_vec){0});
	out.size = 0;
	out.alloc_size = alloc_size;
	out.data = lv_alloc(alloc_size * sizeof_type);
	if (!out.data)
		return ((t_vec){0});
	out.sizeof_type = sizeof_type;
	return (out);
}
