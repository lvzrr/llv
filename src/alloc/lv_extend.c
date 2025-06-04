/**
 * lv_extend.c
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
 * Function: lv_extend
 * -------------------
 * Extends a memory block by allocating a new block of n + size bytes,
 * copying the original data, and freeing the old block.
 *
 * Parameters:
 *   ptr  - original memory block (can be NULL)
 *   n    - size of data currently stored in ptr
 *   size - number of additional bytes to add
 *
 * Returns:
 *   Pointer to the new extended memory block, or NULL on failure.
 *
 * Notes:
 *   - Always frees the original pointer.
 *   - Returns NULL if size is zero and ptr is non-NULL.
 *   - Memory is not zero-initialized.
 */

void	*lv_extend(void *ptr, size_t n, size_t size)
{
	unsigned char	*p2;

	if (size > SIZE_MAX - n || (size == 0 && ptr))
		return (lv_free(&ptr), NULL);
	if (!ptr)
		return (lv_alloc(n + size));
	p2 = lv_alloc(n + size);
	if (!p2)
		return (NULL);
	lv_memmove(p2, ptr, n);
	return (lv_free(&ptr), p2);
}
