/**
 * lv_memformat.c
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
 * Function: lv_memformat
 * ----------------------
 * Allocates a new memory block, copies the contents of an existing block into it,
 * and then frees the original memory block. This function effectively replaces
 * an existing memory region with a new, potentially re-allocated and copied version.
 *
 * Parameters:
 * ptr  - A pointer to the source memory block to be duplicated and then freed.
 * If NULL, the function will return NULL.
 * size - The number of bytes to allocate for the new block and to copy from 'ptr'.
 * If 0, the function will return NULL.
 *
 * Returns:
 * A pointer to the newly allocated and copied memory block on success.
 * NULL if 'ptr' is NULL, 'size' is 0, or on allocation failure.
 *
 * Notes:
 * - This function internally uses `lv_alloc` (via `lv_memclone`),
 * meaning the returned memory block is aligned as per `lv_alloc`'s
 * specifications and can be safely deallocated using `lv_free`.
 * - **Crucially, the original `ptr` passed to the function is freed
 * before returning the new pointer.** Ensure `ptr` was originally
 * allocated by `malloc` or an `lv_` allocation function.
 * - This function is useful for "reformatting" or replacing a memory block
 * while maintaining proper alignment and freeing the old one.
 */

void	*lv_memformat(void *ptr, size_t size)
{
	void	*fmt;

	if (!ptr || !size)
		return (NULL);
	fmt = lv_memclone(ptr, size);
	return (free(ptr), fmt);
}
