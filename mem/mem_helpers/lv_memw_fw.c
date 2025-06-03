/**
 * lv_memw_fw.c
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
 * Function: _copy_u8_fwd
 * ----------------------
 * Copies a memory region byte-by-byte (8-bit) in a forward direction.
 * This is a helper for `memcpy`-like operations for unaligned or small remaining data.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * src  - A pointer to the source memory region.
 * n    - A pointer to the remaining number of bytes to copy.
 * i    - A pointer to the current index within the buffers.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2 bytes where possible, then single bytes,
 * working from the beginning of the specified range forwards.
 */
__attribute__((always_inline))
inline void	_copy_u8_fwd(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u8) * 2)
	{
		((t_u8 *)dest + *i)[0] = ((t_u8 *)src + *i)[0];
		*i += sizeof(t_u8);
		((t_u8 *)dest + *i)[0] = ((t_u8 *)src + *i)[0];
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8) * 2;
	}
	while (*n > 0)
	{
		((t_u8 *)dest + *i)[0] = ((t_u8 *)src + *i)[0];
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
	}
}

/*
 * Function: _copy_u32_fwd
 * -----------------------
 * Copies a memory region in 32-bit (4-byte) word chunks in a forward direction.
 * This is a helper for `memcpy`-like operations, optimized for 32-bit copies.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * src  - A pointer to the source memory region.
 * n    - A pointer to the remaining number of bytes to copy.
 * i    - A pointer to the current index within the buffers.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 32-bit words where possible, then single words.
 * - Assumes appropriate alignment for 32-bit access.
 */


__attribute__((always_inline))
inline void	_copy_u32_fwd(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u32) * 2)
	{
		((t_u32 *)((t_u8 *)dest + *i))[0] = ((t_u32 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u32);
		((t_u32 *)((t_u8 *)dest + *i))[0] = ((t_u32 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32) * 2;
	}
	while (*n >= sizeof(t_u32))
	{
		((t_u32 *)((t_u8 *)dest + *i))[0] = ((t_u32 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32);
	}
}

/*
 * Function: _copy_u64_fwd
 * -----------------------
 * Copies a memory region in 64-bit (8-byte) word chunks in a forward direction.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * src  - A pointer to the source memory region.
 * n    - A pointer to the remaining number of bytes to copy.
 * i    - A pointer to the current index within the buffers.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 64-bit words where possible, then single words.
 * - Assumes appropriate alignment for 64-bit access.
 */

__attribute__((always_inline))
inline void	_copy_u64_fwd(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u64) * 2)
	{
		((t_u64 *)((t_u8 *)dest + *i))[0] = ((t_u64 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u64);
		((t_u64 *)((t_u8 *)dest + *i))[0] = ((t_u64 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64) * 2;
	}
	while (*n >= sizeof(t_u64))
	{
		((t_u64 *)((t_u8 *)dest + *i))[0] = ((t_u64 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64);
	}
}

/*
 * Function: _copy_u128_fwd
 * ------------------------
 * Copies a memory region in 128-bit (16-byte) word chunks in a forward direction.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * src  - A pointer to the source memory region.
 * n    - A pointer to the remaining number of bytes to copy.
 * i    - A pointer to the current index within the buffers.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 128-bit words where possible, then single words.
 * - Assumes appropriate alignment for 128-bit access.
 */

__attribute__((always_inline))
inline void	_copy_u128_fwd(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u128) * 2)
	{
		((t_u128 *)((t_u8 *)dest + *i))[0] = ((t_u128 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u128);
		((t_u128 *)((t_u8 *)dest + *i))[0] = ((t_u128 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128) * 2;
	}
	while (*n >= sizeof(t_u128))
	{
		((t_u128 *)((t_u8 *)dest + *i))[0] = ((t_u128 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128);
	}
}

/*
 * Function: _aligned
 * ------------------
 * Determines the largest common alignment for two memory pointers.
 * This is used to select the most efficient word size (8, 32, 64, or 128-bit)
 * for memory operations like copy, set, or compare.
 *
 * Parameters:
 * dest - A pointer to the first memory region.
 * src  - A pointer to the second memory region.
 * i    - A pointer to the current offset (index) within the buffers.
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

__attribute__((always_inline))
inline t_u8	_aligned(const void *__restrict__ dest,
	const void *__restrict__ src, size_t *i)
{
	t_uptr	d;
	t_uptr	s;

	d = (t_uptr)((t_u8 *)dest + *i);
	s = (t_uptr)((t_u8 *)src + *i);
	if (s == *i)
		s = 128;
	if ((d % sizeof(t_u128) == 0)
		&& (s % sizeof(t_u128) == 0))
		return (128);
	if ((d % sizeof(t_u64) == 0)
		&& (s % sizeof(t_u64) == 0))
		return (64);
	if ((d % sizeof(t_u32) == 0)
		&& (s % sizeof(t_u32) == 0))
		return (32);
	return (0);
}
