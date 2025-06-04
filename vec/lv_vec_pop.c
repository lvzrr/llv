/**
 * lv_vec_pop.c
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
 * Function: lv_vec_pop
 * --------------------
 * Removes the last element from the vector and zeros out the memory
 * that it occupied. The vector's size is decremented.
 *
 * Parameters:
 * v - A pointer to the `t_vec` structure from which to pop an element.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This function is `inline` for performance.
 * - If `v` is NULL, `v->data` is NULL, or the vector is empty (`v->size == 0`),
 * the function does nothing.
 * - It uses `lv_bzero` to clear the memory of the popped element.
 * - The allocated capacity of the vector remains unchanged.
 */

inline void	lv_vec_pop(t_vec *__restrict__ v)
{
	void	*ptr;

	if (!v || !v->data || v->size == 0)
		return ;
	v->size--;
	ptr = (t_u8 *)v->data + (v->size * v->sizeof_type);
	lv_bzero(ptr, v->sizeof_type);
}
