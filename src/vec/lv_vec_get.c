/**
 * lv_vec_get.c
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
 * Function: lv_vec_get
 * --------------------
 * Retrieves a pointer to a constant element at a specified index within the vector.
 *
 * Parameters:
 * vec - A pointer to the `t_vec` structure.
 * idx - The index of the element to retrieve.
 *
 * Returns:
 * A constant `void` pointer to the element at `idx` if successful,
 * or NULL if `vec` is invalid, the vector is empty, or `idx` is out of bounds.
 *
 * Notes:
 * - The returned pointer is constant, meaning the data it points to
 * should not be modified directly. Use `lv_vec_get_mut` for mutable access.
 * - The index `idx` is zero-based.
 */

const void	*lv_vec_get(t_vec *vec, size_t idx)
{
	t_u8	*raw;

	if (!vec || !vec->size || idx > vec->size)
		return (NULL);
	raw = (t_u8 *)vec->data;
	return (raw + (vec->sizeof_type * idx));
}

/*
 * Function: lv_vec_get_mut
 * ------------------------
 * Retrieves a pointer to a mutable element at a specified index within the vector.
 *
 * Parameters:
 * vec - A pointer to the `t_vec` structure.
 * idx - The index of the element to retrieve.
 *
 * Returns:
 * A mutable `void` pointer to the element at `idx` if successful,
 * or NULL if `vec` is invalid, the vector is empty, or `idx` is out of bounds.
 *
 * Notes:
 * - The returned pointer allows direct modification of the element's data.
 * - The index `idx` is zero-based.
 */

void	*lv_vec_get_mut(t_vec *vec, size_t idx)
{
	t_u8	*raw;

	if (!vec || !vec->size || idx > vec->size)
		return (NULL);
	raw = (t_u8 *)vec->data;
	return (raw + (vec->sizeof_type * idx));
}

/*
 * Function: lv_vec_get_clone
 * --------------------------
 * Allocates new memory and copies an element from the vector at a
 * specified index into this new memory.
 *
 * Parameters:
 * vec - A pointer to the `t_vec` structure.
 * idx - The index of the element to clone.
 *
 * Returns:
 * A `void` pointer to the newly allocated and copied element if successful,
 * or NULL if `vec` is invalid, the vector is empty, `idx` is out of bounds,
 * or memory allocation for the clone fails.
 *
 * Notes:
 * - This function performs a deep copy of the element.
 * - The caller is responsible for freeing the returned memory using `lv_free`
 * (or equivalent).
 * - The index `idx` is zero-based.
 * - It uses `lv_memclone` to perform the actual cloning.
 */

void	*lv_vec_get_clone(t_vec *vec, size_t idx)
{
	t_u8	*raw;

	if (!vec || !vec->size || idx > vec->size)
		return (NULL);
	raw = (t_u8 *)vec->data;
	return(lv_memclone(raw + (vec->sizeof_type * idx),
		vec->sizeof_type));
}
