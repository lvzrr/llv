/**
 * lv_realloc.c
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

#include "alloc.h"

/*
 * Function: lv_realloc
 * --------------------
 * Reallocates memory to a new size, copying up to n bytes from the old block.
 *
 * Parameters:
 *   ptr  - original memory block (can be NULL)
 *   n    - number of bytes to copy from the original block
 *   size - new size for the reallocated memory
 *
 * Returns:
 *   Pointer to the new memory block, or NULL on failure.
 *
 * Notes:
 *   - Always frees the original pointer.
 *   - Returns NULL if size is zero.
 */

void	*lv_realloc(void *ptr, size_t n, size_t size)
{
	void	*p;

	if (!size)
		return (lv_free(&ptr), NULL);
	if (!ptr)
		return (lv_alloc(size));
	p = lv_alloc(size);
	if (!p)
		return (lv_free(&ptr), NULL);
	if (size < n)
		n = size;
	lv_memmove(p, ptr, n);
	if (ptr)
		lv_free(&ptr);
	return (p);
}
