/**
 * lv_extend_zero.c
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
 * Function: lv_extend_zero
 * ------------------------
 * Same as lv_extend, but zero-initializes the new memory.
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
 *   - New memory is zero-initialized.
 */

void	*lv_extend_zero(void *ptr, size_t n, size_t size)
{
	unsigned char	*p2;

	if (size > SIZE_MAX - n || (size == 0 && ptr))
		return (lv_free(&ptr), NULL);
	if (!ptr)
		return (lv_calloc(n + size, 1));
	p2 = lv_calloc(n + size, 1);
	if (!p2)
		return (NULL);
	lv_memmove(p2, ptr, n);
	return (lv_free(&ptr), p2);
}
