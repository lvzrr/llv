/**
 * lv_vec_fit.c
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
 * Function: lv_vec_fit
 * --------------------
 * Resizes the vector's allocated memory to exactly fit its current number
 * of elements (`v->size`). This effectively deallocates any unused capacity.
 *
 * Parameters:
 * v - A pointer to the `t_vec` structure to be fitted.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - If `v` is NULL, or if the vector is empty (`v->size` is 0), or if
 * `v->alloc_size` is 0, the function does nothing.
 * - It uses `lv_realloc` to resize the memory block. If `lv_realloc` fails,
 * the function returns without changing the vector's state.
 * - After a successful fit, `v->alloc_size` will be equal to `v->size`.
 */

void	lv_vec_fit(t_vec *v)
{
	void	*data;

	if (!v || !v->size || !v->alloc_size)
		return ;
	data = lv_realloc(v->data, v->alloc_size * v->sizeof_type,
			v->size * v->sizeof_type);
	if (!data)
		return ;
	v->data = data;
	v->alloc_size = v->size;
}
