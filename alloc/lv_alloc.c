/**
 * lv_alloc.c
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
#include "printf.h"

/*
 * Function: lv_alloc
 * ------------------
 * Allocates a memory block with 128-byte alignment.
 *
 * Parameters:
 *   size - size of memory to allocate in bytes
 *
 * Returns:
 *   A pointer to the allocated memory on success.
 *   NULL on failure.
 *
 * Notes:
 *   - Uses posix_memalign to ensure alignment.
 *   - Intended for optimized use with lv_mem* operations.
 */

void	*lv_alloc(size_t size)
{
	void	*new_alloc;

	if (posix_memalign(&new_alloc, 128, size) != 0)
		return (NULL);
	return (new_alloc);
}
