/**
 * lv_vec_free.c
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
 * Function: lv_vec_free
 * ---------------------
 * Deallocates the memory associated with a vector and resets its
 * internal state to zero. This function should be called when a
 * vector is no longer needed to prevent memory leaks.
 *
 * Parameters:
 * v - A pointer to the `t_vec` structure to be freed.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - If `v` is NULL, the function does nothing.
 * - It uses `lv_free` to deallocate the `data` pointer.
 * - After freeing, all members of the `t_vec` structure (`data`, `size`,
 * `alloc_size`, `sizeof_type`) are set to 0.
 */

void	lv_vec_free(t_vec *v)
{
	void	*tmp;

	if (!v)
		return ;
	tmp = (void *)v->data;
	lv_free(&tmp);
	v->data = NULL;
	v->size = 0;
	v->alloc_size = 0;
	v->sizeof_type = 0;
}
