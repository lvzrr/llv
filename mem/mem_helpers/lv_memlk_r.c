/**
 * lv_memlk_r.c
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
 * Function: _look4_u8_fwd_unsafe
 * ------------------------------
 * Searches for the first occurrence of a specific 8-bit value (byte)
 * within a memory region, advancing forward, without bounds checking.
 * It assumes the value will eventually be found or the memory is valid.
 *
 * Parameters:
 * ptr - A pointer to the memory region to search.
 * x   - The 8-bit value (byte) to search for.
 * i   - A pointer to the current index within the buffer.
 *
 * Returns:
 * A pointer to the first occurrence of `x`.
 *
 * Notes:
 * - This is an inline helper function.
 * - It's "unsafe" because it performs an infinite loop (`while (true)`)
 * and relies on the caller to ensure `x` will be found within valid memory.
 * - Processes memory in chunks of 2 bytes.
 */

__attribute__((always_inline))
inline void	*_look4_u8_fwd_unsafe(void *__restrict__ ptr,
	t_u8 x,
	size_t *__restrict__ i)
{
	t_u8	*d;

	d = (t_u8 *) ptr + *i;
	while (true)
	{
		if (*d++ == x)
			break;
		(*i)++;
		if (*d++ == x)
			break;
		(*i)++;
	}
	return ((t_u8 *)d - 1);
}

/*
 * Function: _look4_u32_fwd
 * ------------------------
 * Searches for the first occurrence of a specific 32-bit value (or a byte
 * within it) within a memory region, advancing forward. This uses optimized
 * 32-bit word comparisons.
 *
 * Parameters:
 * ptr - A pointer to the memory region to search.
 * x   - The 32-bit value to search for (used as a mask for `_lookup_u32`).
 * n   - A pointer to the remaining number of bytes to search.
 * i   - A pointer to the current index within the buffer.
 *
 * Returns:
 * A pointer to the first occurrence of `x` (or a byte matching `x` within a word)
 * if found, NULL otherwise.
 *
 * Notes:
 * - This is an inline helper function.
 * - It assumes 4-byte alignment for `ptr` and processes memory in 32-bit words,
 * using `_lookup_u32` to find specific byte matches within those words.
 */

__attribute__((always_inline))
inline void	*_look4_u32_fwd(void *__restrict__ ptr,
	t_u32 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u32	*d;
	int		lk;

	d = (t_u32 *) __builtin_assume_aligned(ptr, 4) + *i;
	while (*n >= sizeof(t_u32) * 2)
	{
		lk = _lookup_u32(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u32) + lk);
		lk = _lookup_u32(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u32) + lk);
		*n -= sizeof(t_u32) * 2;
		*i += sizeof(t_u32) * 2;
	}
	while (*n >= sizeof(t_u32))
	{
		lk = _lookup_u32(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u32) + lk);
		*n -= sizeof(t_u32);
		*i += sizeof(t_u32);
	}
	return (NULL);
}

/*
 * Function: _look4_u64_fwd
 * ------------------------
 * Searches for the first occurrence of a specific 64-bit value (or a byte
 * within it) within a memory region, advancing forward. This uses optimized
 * 64-bit word comparisons.
 *
 * Parameters:
 * ptr - A pointer to the memory region to search.
 * x   - The 64-bit value to search for (used as a mask for `_lookup_u64`).
 * n   - A pointer to the remaining number of bytes to search.
 * i   - A pointer to the current index within the buffer.
 *
 * Returns:
 * A pointer to the first occurrence of `x` (or a byte matching `x` within a word)
 * if found, NULL otherwise.
 *
 * Notes:
 * - This is an inline helper function.
 * - It assumes 8-byte alignment for `ptr` and processes memory in 64-bit words,
 * using `_lookup_u64` to find specific byte matches within those words.
 */

__attribute__((always_inline))
inline void	*_look4_u64_fwd(void *__restrict__ ptr,
	t_u64 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u64	*d;
	int		lk;

	d = (t_u64 *) __builtin_assume_aligned(ptr, 8) + *i;
	while (*n >= sizeof(t_u64) * 2)
	{
		lk = _lookup_u64(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u64) + lk);
		lk = _lookup_u64(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u64) + lk);
		*n -= sizeof(t_u64) * 2;
		*i += sizeof(t_u64) * 2;
	}
	while (*n >= sizeof(t_u64))
	{
		lk = _lookup_u64(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u64) + lk);
		*n -= sizeof(t_u64);
		*i += sizeof(t_u64);
	}
	return (NULL);
}

/*
 * Function: _look4_u128_fwd
 * -------------------------
 * Searches for the first occurrence of a specific 128-bit value (or a byte
 * within it) within a memory region, advancing forward. This uses optimized
 * 128-bit word comparisons.
 *
 * Parameters:
 * ptr - A pointer to the memory region to search.
 * x   - The 128-bit value to search for (used as a mask for `_lookup_u128`).
 * n   - A pointer to the remaining number of bytes to search.
 * i   - A pointer to the current index within the buffer.
 *
 * Returns:
 * A pointer to the first occurrence of `x` (or a byte matching `x` within a word)
 * if found, NULL otherwise.
 *
 * Notes:
 * - This is an inline helper function.
 * - It assumes 8-byte alignment for `ptr` (though 16-byte would be ideal for 128-bit)
 * and processes memory in 128-bit words, using `_lookup_u128` to find specific
 * byte matches within those words.
 */

__attribute__((always_inline))
inline void	*_look4_u128_fwd(void *__restrict__ ptr,
	t_u128 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u128	*d;
	int		lk;
	d = (t_u128 *) __builtin_assume_aligned(ptr, 8) + *i;
	while (*n >= sizeof(t_u128) * 2)
	{
		lk = _lookup_u128(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u128) + lk);
		lk = _lookup_u128(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u128) + lk);
		*n -= sizeof(t_u128) * 2;
		*i += sizeof(t_u128) * 2;
	}
	while (*n >= sizeof(t_u128))
	{
		lk = _lookup_u128(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u128) + lk);
		*n -= sizeof(t_u128);
		*i += sizeof(t_u128);
	}
	return (NULL);
}
