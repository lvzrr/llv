/**
 * lv_memclone.c
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

#include "mem.h"

/*
 * Function: lv_memclone
 * ---------------------
 * Allocates a new memory region of `size` bytes and copies the contents
 * of the memory area pointed to by `ptr` into this new region.
 *
 * Parameters:
 * ptr  - A pointer to the source memory region to be cloned.
 * size - The number of bytes to clone.
 *
 * Returns:
 * A pointer to the newly allocated and populated memory region if successful,
 * or a null pointer if `ptr` is NULL, `size` is 0, or memory allocation fails.
 *
 * Notes:
 * - This function performs a deep copy of the memory.
 * - It relies on `lv_alloc` for memory allocation and `lv_memmove` for copying.
 * - The caller is responsible for freeing the returned memory using `lv_free`
 * (or equivalent).
 */

void	*lv_memclone(void *__restrict__ ptr, size_t size)
{
	void	*new_reg;

	if (!ptr || size == 0)
		return (NULL);
	new_reg = lv_alloc(size);
	if (!new_reg)
		return (NULL);
	lv_memmove(new_reg, ptr, size);
	return (new_reg);
}
