/**
 * lv_memcm_r.c
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
 * Function: _cmp_u8
 * -----------------
 * Compares two memory regions byte-by-byte (8-bit) in a forward direction.
 * This is a helper for `memcmp`-like operations for unaligned or small remaining data.
 *
 * Parameters:
 * dest - A pointer to the first memory region.
 * src  - A pointer to the second memory region.
 * n    - A pointer to the remaining number of bytes to compare.
 * i    - A pointer to the current index within the buffers.
 *
 * Returns:
 * An integer less than, equal to, or greater than zero if `dest` is found,
 * respectively, to be less than, to match, or be greater than `src`.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2 bytes where possible, then single bytes.
 */

LV_INLINE  inline ssize_t	_cmp_u8(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u8) * 2)
	{
		if (((t_u8 *)dest + *i)[0]
			!= ((t_u8 *)src + *i)[0])
			return (ssize_t)(((t_u8 *)dest + *i)[0]
				- ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
		if (((t_u8 *)dest + *i)[0]
			!= ((t_u8 *)src + *i)[0])
			return (ssize_t)(((t_u8 *)dest + *i)[0]
				- ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
	}
	while (*n >= sizeof(t_u8))
	{
		if (((t_u8 *)dest + *i)[0]
			!= ((t_u8 *)src + *i)[0])
			return (ssize_t)(((t_u8 *)dest + *i)[0]
				- ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
	}
	return (0);
}

/*
 * Function: _cmp_u32
 * ------------------
 * Compares two memory regions in 32-bit (4-byte) word chunks in a forward direction.
 * This is a helper for `memcmp`-like operations, optimized for 32-bit comparisons.
 *
 * Parameters:
 * dest - A pointer to the first memory region.
 * src  - A pointer to the second memory region.
 * n    - A pointer to the remaining number of bytes to compare.
 * i    - A pointer to the current index within the buffers.
 *
 * Returns:
 * An integer based on the difference of the first differing 32-bit word,
 * or 0 if no difference found within `n` bytes.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 32-bit words where possible, then single words.
 * - Assumes appropriate alignment for 32-bit access.
 */

LV_INLINE  inline ssize_t    _cmp_u32(void *__restrict__ dest,
    const void * __restrict__ src,
    size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u32) * 2)
	{
		if (((t_u32 *)((t_u8 *)dest + *i))[0]
			!= ((t_u32 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u32 *)((t_u8 *)dest + *i))[0]
				- ((t_u32 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32);
		if (((t_u32 *)((t_u8 *)dest + *i))[0]
			!= ((t_u32 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u32 *)((t_u8 *)dest + *i))[0]
				- ((t_u32 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32);
	}
	while (*n >= sizeof(t_u32))
	{
		if (((t_u32 *)((t_u8 *)dest + *i))[0]
			!= ((t_u32 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u32 *)((t_u8 *)dest + *i))[0]
				- ((t_u32 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32);
	}
	return (0);
}

/*
 * Function: _cmp_u64
 * ------------------
 * Compares two memory regions in 64-bit (8-byte) word chunks in a forward direction.
 *
 * Parameters:
 * dest - A pointer to the first memory region.
 * src  - A pointer to the second memory region.
 * n    - A pointer to the remaining number of bytes to compare.
 * i    - A pointer to the current index within the buffers.
 *
 * Returns:
 * An integer based on the difference of the first differing 64-bit word,
 * or 0 if no difference found within `n` bytes.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 64-bit words where possible, then single words.
 * - Assumes appropriate alignment for 64-bit access.
 */

#include "mem.h"

LV_SIMD_AVX2 LV_INLINE  inline ssize_t	_cmp_u64(void *__restrict__ dest,
	const void * __restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u64) * 2)
	{
		if (((t_u64 *)((t_u8 *)dest + *i))[0]
			!= ((t_u64 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u64 *)((t_u8 *)dest + *i))[0]
				- ((t_u64 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64);
		if (((t_u64 *)((t_u8 *)dest + *i))[0]
			!= ((t_u64 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u64 *)((t_u8 *)dest + *i))[0]
				- ((t_u64 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64);
	}
	while (*n >= sizeof(t_u64))
	{
		if (((t_u64 *)((t_u8 *)dest + *i))[0]
			!= ((t_u64 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u64 *)((t_u8 *)dest + *i))[0]
				- ((t_u64 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64);
	}
	return (0);
}

/*
 * Function: _cmp_u128
 * -------------------
 * Compares two memory regions in 128-bit (16-byte) word chunks in a forward direction.
 *
 * Parameters:
 * dest - A pointer to the first memory region.
 * src  - A pointer to the second memory region.
 * n    - A pointer to the remaining number of bytes to compare.
 * i    - A pointer to the current index within the buffers.
 *
 * Returns:
 * An integer based on the difference of the first differing 128-bit word,
 * or 0 if no difference found within `n` bytes.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 128-bit words where possible, then single words.
 * - Assumes appropriate alignment for 128-bit access.
 */

LV_SIMD_AVX2 LV_INLINE inline ssize_t	_cmp_u128(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u128) * 2)
	{
		if (((t_u128 *)((t_u8 *)dest + *i))[0]
			!= ((t_u128 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u128 *)((t_u8 *)dest + *i))[0]
				- ((t_u128 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128);
		if (((t_u128 *)((t_u8 *)dest + *i))[0]
			!= ((t_u128 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u128 *)((t_u8 *)dest + *i))[0]
				- ((t_u128 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128);
	}
	while (*n >= sizeof(t_u128))
	{
		if (((t_u128 *)((t_u8 *)dest + *i))[0]
			!= ((t_u128 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u128 *)((t_u8 *)dest + *i))[0]
				- ((t_u128 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128);
	}
	return (0);
}
