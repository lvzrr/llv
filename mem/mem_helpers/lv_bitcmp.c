/**
 * lv_bitcmp.c
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
 * Function: _lookup_u32
 * ---------------------
 * Locates the first differing byte between a 32-bit word and a mask.
 * Used for optimized byte-wise comparison or lookup within a 32-bit block.
 *
 * Parameters:
 * word - The 32-bit unsigned integer to compare.
 * mask - The 32-bit unsigned integer mask (e.g., character to find repeated).
 *
 * Returns:
 * The byte offset (0-3) of the first differing byte if found, -1 otherwise.
 *
 * Notes:
 * - This is an inline, hot helper function for performance.
 * - It uses bitwise operations to efficiently find the position of the first
 * difference. The result is then right-shifted by 3 to get the byte offset.
 */

__attribute__((always_inline))
__attribute__((hot))
inline int _lookup_u32(t_u32 word, t_u32 mask)
{
    t_u32 diff;
    t_u32 t;

	t = (t_u128)0;
    diff = word ^ mask;
    t = (diff - LONES_32) & ~diff & HIGHS_32;
    if (!t)
        return (-1);
    return (lv_memctz_u32(t) >> 3);
}

/*
 * Function: _lookup_u64
 * ---------------------
 * Locates the first differing byte between a 64-bit word and a mask.
 *
 * Parameters:
 * word - The 64-bit unsigned integer to compare.
 * mask - The 64-bit unsigned integer mask.
 *
 * Returns:
 * The byte offset (0-7) of the first differing byte if found, -1 otherwise.
 *
 * Notes:
 * - This is an inline, hot helper function for performance.
 * - Similar to `_lookup_u32` but for 64-bit words.
 */

__attribute__((always_inline))
__attribute__((hot))
inline int _lookup_u64(t_u64 word, t_u64 mask)
{
    t_u64 diff;
    t_u64 t;

	t = (t_u128)0;
    diff = word ^ mask;
    t = (diff - LONES_64) & ~diff & HIGHS_64;
    if (!t)
        return (-1);
    return (lv_memctz_u64(t) >> 3);
}

/*
 * Function: _lookup_u128
 * ----------------------
 * Locates the first differing byte between a 128-bit word and a mask.
 *
 * Parameters:
 * word - The 128-bit unsigned integer to compare.
 * mask - The 128-bit unsigned integer mask.
 *
 * Returns:
 * The byte offset (0-15) of the first differing byte if found, -1 otherwise.
 *
 * Notes:
 * - This is an inline, hot helper function for performance.
 * - It splits the 128-bit values into two 64-bit parts and uses `_lookup_u64`
 * on each part, adjusting the offset for the high part.
 */

__attribute__((always_inline))
__attribute__((hot))
inline int _lookup_u128(t_u128 word, t_u128 mask)
{
	int		lkup;
	t_u64	low_word;
	t_u64	high_word;
	t_u64 	low_mask;
	t_u64	high_mask;


	high_mask = (t_u64)(mask >> 64);
	low_mask = (t_u64)mask;
	high_word = (t_u64)(word >> 64);
	low_word = (t_u64)word;
	lkup = _lookup_u64(low_word, low_mask);
	if (lkup != -1)
	{
		return lkup;
	}
	lkup = _lookup_u64(high_word, high_mask);
	if (lkup != -1)
	{
		return 64 + lkup;
	}
	return (-1);
}

/*
 * Function: _look4_u8_fwd
 * -----------------------
 * Searches for the first occurrence of a specific 8-bit value (byte)
 * within a memory region, advancing forward. This is a byte-wise search.
 *
 * Parameters:
 * ptr - A pointer to the memory region to search.
 * x   - The 8-bit value (byte) to search for.
 * n   - A pointer to the remaining number of bytes to search.
 * i   - A pointer to the current index within the buffer.
 *
 * Returns:
 * A pointer to the first occurrence of `x` if found, NULL otherwise.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in a forward direction, in chunks of 2 bytes
 * where possible, then single bytes.
 */

#include "mem.h"

LV_INLINE inline void	*_look4_u8_fwd(void *__restrict__ ptr,
	t_u8 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u8	*d;

	d = (t_u8 *) ptr + *i;
	while (*n >= 2)
	{
		if (*d++ == x)
			return ((t_u8 *)d - 1);
		if (*d++ == x)
			return ((t_u8 *)d - 1);
		(*n) -= 2;
		(*i) += 2;
	}
	while (*n > 0)
	{
		if (*d++ == x)
			return ((t_u8 *)d - 1);
		(*n)--;
		(*i)++;
	}
	return (NULL);
}
