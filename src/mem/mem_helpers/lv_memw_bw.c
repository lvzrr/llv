/**
 * lv_memw_bw.c
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
 * Function: _copy_u8_bw
 * ---------------------
 * Copies a memory region byte-by-byte (8-bit) in a backward direction.
 * This is a helper for `memmove`-like operations when source and destination
 * overlap and backward copy is required.
 *
 * Parameters:
 * dest - A pointer to the destination memory region (adjusted for backward copy).
 * src  - A pointer to the source memory region (adjusted for backward copy).
 * n    - A pointer to the remaining number of bytes to copy.
 * i    - A pointer to the current index within the buffers (from end).
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2 bytes where possible, then single bytes,
 * working from the end of the specified range backwards.
 * - The `dest` and `src` pointers typically need to be adjusted to point
 * to the end of the regions before calling this.
 */

LV_INLINE inline void	_copy_u8_bw(void *__restrict__ dest,
	const void *__restrict__ src, size_t *__restrict__ n,
	size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u8) * 2)
	{
		((t_u8 *)dest + *i - 2)[1] = ((t_u8 *)src + *i - 2)[1];
		*i += sizeof(t_u8);
		((t_u8 *)dest + *i - 2)[0] = ((t_u8 *)src + *i - 2)[0];
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8) * 2;
	}
	while (*n >= sizeof(t_u8) * 2)
	{
		dest = (void *)(((t_u8 *)dest) - sizeof(t_u8));
		src = (void *)(((t_u8 *)src) - sizeof(t_u8));
		((t_u8 *)dest + *i)[0] = ((t_u8 *)src + *i)[0];
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
	}
}

/*
 * Function: _copy_u32_bw
 * ----------------------
 * Copies a memory region in 32-bit (4-byte) word chunks in a backward direction.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * src  - A pointer to the source memory region.
 * n    - A pointer to the remaining number of bytes to copy.
 * i    - A pointer to the current index within the buffers (from end).
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 32-bit words where possible, then single words,
 * working from the end of the specified range backwards.
 * - Assumes appropriate alignment for 32-bit access.
 */

LV_INLINE inline void	_copy_u32_bw(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u32) * 2)
	{
		((t_u32 *)((t_u8 *)dest + *i) - 2)[1]
			= ((t_u32 *)((t_u8 *)src + *i) - 2)[1];
		*i += sizeof(t_u32);
		((t_u32 *)((t_u8 *)dest + *i) - 2)[0]
			= ((t_u32 *)((t_u8 *)src + *i)- 2)[0];
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32) * 2;
	}
	while (*n >= sizeof(t_u32))
	{
		((t_u32 *)((t_u8 *)dest + *i) - 2)[1]
			= ((t_u32 *)((t_u8 *)src + *i) - 2)[1];
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32);
	}
}

/*
 * Function: _copy_u64_bw
 * ----------------------
 * Copies a memory region in 64-bit (8-byte) word chunks in a backward direction.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * src  - A pointer to the source memory region.
 * n    - A pointer to the remaining number of bytes to copy.
 * i    - A pointer to the current index within the buffers (from end).
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 64-bit words where possible, then single words,
 * working from the end of the specified range backwards.
 * - Assumes appropriate alignment for 64-bit access.
 */

LV_INLINE inline void	_copy_u64_bw(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u64) * 2)
	{
		((t_u64 *)((t_u8 *)dest + *i - 2))[1]
			= ((t_u64 *)((t_u8 *)src + *i - 2))[1];
		*i += sizeof(t_u64);
		((t_u64 *)((t_u8 *)dest + *i) - 2)[0]
			= ((t_u64 *)((t_u8 *)src + *i) - 2)[0];
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64) * 2;
	}
	while (*n >= sizeof(t_u64))
	{
		((t_u64 *)((t_u8 *)dest + *i) - 2)[0]
			= ((t_u64 *)((t_u8 *)src + *i) - 2)[0];
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64);
	}
}

/*
 * Function: _copy_u128_bw
 * -----------------------
 * Copies a memory region in 128-bit (16-byte) word chunks in a backward direction.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * src  - A pointer to the source memory region.
 * n    - A pointer to the remaining number of bytes to copy.
 * i    - A pointer to the current index within the buffers (from end).
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 128-bit words where possible, then single words,
 * working from the end of the specified range backwards.
 * - Assumes appropriate alignment for 128-bit access.
 */

LV_INLINE inline void	_copy_u128_bw(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u128) * 2)
	{
		((t_u128 *)((t_u8 *)dest + *i) - 2)[1]
			= ((t_u128 *)((t_u8 *)src + *i) - 2)[1];
		*i += sizeof(t_u128);
		((t_u128 *)((t_u8 *)dest + *i) - 2)[0]
			= ((t_u128 *)((t_u8 *)src + *i) - 2)[0];
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128) * 2;
	}
	while (*n >= sizeof(t_u128))
	{
		((t_u128 *)((t_u8 *)dest + *i) - 2)[0]
			= ((t_u128 *)((t_u8 *)src + *i) - 2)[0];
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128);
	}
}
