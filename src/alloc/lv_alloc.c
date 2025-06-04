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

/*
 * Function: lv_alloc_align
 * ------------------------
 * Allocates a memory block of a specified size with a guaranteed alignment.
 * It ensures that the returned pointer is a multiple of 'align'.
 *
 * Parameters:
 * size  - The desired size of the memory block in bytes.
 * align - The required alignment boundary (must be a power of 2).
 *
 * Returns:
 * A pointer to the aligned memory block on success.
 * NULL on failure (e.g., invalid alignment, insufficient memory, or size overflow).
 *
 * Notes:
 * - The actual memory requested from 'malloc' (`tab`) is larger than 'size' to
 * accommodate padding for alignment and a hidden pointer.
 * - The original pointer returned by 'malloc' (`tab`) is stored `sizeof(void*)` bytes
 * *before* the aligned address (`ac`) that is returned to the user. This is crucial
 * for the corresponding `lv_free` function to correctly deallocate the entire block.
 * - Uses standard pointer arithmetic and bitwise operations for alignment,
 * making it portable and compatible with various 'malloc' implementations.
 */

__attribute__((malloc))
void	*lv_alloc_align(size_t size, size_t align)
{
	void	*tab;
	size_t	alloc_size;
	t_uptr	cc;
	void	*ac;

	if ((align == 0) || ((align & (align - 1)) != 0))
		return (NULL);
	if (align < sizeof(void *))
		align = sizeof(void *);
	if (size > SIZE_MAX - (align - 1) - sizeof(void *))
		return (NULL);
	alloc_size = sizeof(void *) + (align - 1) + size;
	tab = malloc(alloc_size);
	if (!tab)
		return (NULL);
	cc = (t_uptr)tab + sizeof(void *);
	ac = (void *)((cc + (align - 1)) & ~(align - 1));
	return (((void **)ac)[-1] = tab, ac);
}

/*
 * Function: lv_alloc
 * ------------------
 * Allocates a memory block with 128-byte alignment.
 *
 * Parameters:
 * size - size of memory to allocate in bytes
 *
 * Returns:
 * A pointer to the allocated memory on success.
 * NULL on failure.
 *
 * Notes:
 * - Uses lv_alloc_align to ensure alignment.
 * - Intended for optimized use with lv_mem* operations.
 */

__attribute__((malloc))
void	*lv_alloc(size_t size)
{
	void	*new_alloc;

	new_alloc = lv_alloc_align(size, DEF_ALIGN);
	if (!new_alloc)
		return (NULL);
	return (new_alloc);
}
