/**
 * lv_vec_peek_last.c
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
 * Function: lv_vec_peek_last
 * --------------------------
 * Returns a pointer to the last element in the vector without removing it.
 *
 * Parameters:
 * v - A pointer to the `t_vec` structure.
 *
 * Returns:
 * A mutable `void` pointer to the last element if the vector is not empty,
 * or NULL if `v` is NULL. If the vector is empty, it returns `v->data`
 * (which might be NULL if the vector was never initialized or was freed).
 *
 * Notes:
 * - This function is `inline` for performance.
 * - It does not perform any bounds checking beyond `v` being NULL and `v->size` being 0.
 * - The returned pointer allows direct modification of the element.
 */

inline void	*lv_vec_peek_last(t_vec *__restrict__ v)
{
	if (!v)
		return (NULL);
	if (v->size == 0)
		return (v->data);
	return ((t_u8 *)v->data + (v->size - 1)
		* v->sizeof_type);
}
