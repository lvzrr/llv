/**
 * _aligned.c
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
 * Function: _aligned
 * ------------------
 * Determines the largest common alignment for two memory pointers.
 * This is used to select the most efficient word size (8, 32, 64, or 128-bit)
 * for memory operations like copy, set, or compare.
 *
 * Parameters:
 * dest - A pointer to the first memory region.
 * src - A pointer to the second memory region.
 * i  - A pointer to the current offset (index) within the buffers.
 *
 * Returns:
 * The largest power of 2 (in bits: 128, 64, 32, or 0 for byte-wise)
 * that both `dest` and `src` are currently aligned to at the given offset.
 *
 * Notes:
 * - This is an inline helper function.
 * - It helps optimize memory operations by allowing word-sized access
 * when memory is appropriately aligned.
 * - `s == *i` is likely a check for `src` being `NULL` or very early in buffer.
 */

LV_INLINE_HOT LV_CONST inline t_u8	_aligned(const void *__restrict__ dest,
	const void *__restrict__ src, size_t *i)
{
	t_uptr	d;
	t_uptr	s;

	d = (t_uptr)((t_u8 *)dest + *i);
	s = (t_uptr)((t_u8 *)src + *i);

	if (!(d & 127)
		&& !(s & 127))
		return (128);
	if (!(d & 63)
		&& !(s & 63))
		return (64);
	if (!(d & 31)
		&& !(s & 31))
		return (32);
	return (0);
}
