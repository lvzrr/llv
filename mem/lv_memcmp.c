/**
 * lv_memcmp.c
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
 * Function: _alinger
 * ------------------
 * Helper function for `lv_memcmp` to handle initial unaligned bytes
 * and attempt to align the pointers for more efficient word-sized comparisons.
 * It compares bytes two at a time until alignment is achieved or a difference is found.
 *
 * Parameters:
 * dest - A pointer to the first memory region.
 * src  - A pointer to the second memory region.
 * n    - A pointer to the remaining number of bytes to compare. This value is decremented.
 * r    - A pointer to a `t_u8` that will store the alignment status from `_aligned`.
 * i    - A pointer to the current index within the buffers. This value is incremented.
 *
 * Returns:
 * The difference between the first differing bytes, or 0 if no difference is found
 * within the handled unaligned section. A negative value if `dest` byte is less
 * than `src` byte, positive if greater.
 *
 * Notes:
 * - This function is `always_inline` for performance critical paths.
 * - It updates `n` and `i` to reflect the bytes processed.
 * - `*r` is set by calls to `_aligned` to indicate if alignment has been achieved.
 */

__attribute__((always_inline))
inline ssize_t    _alinger(void *__restrict__ dest,
	const void *__restrict__ src, size_t *n, t_u8 *r,
	size_t *__restrict__ i)
{
	while (*n >= 2 && !*r)
	{
		if(((t_u8 *)dest + *i)[0] != ((t_u8 *)src + *i)[0])
			return (((t_u8 *)dest + *i)[0] - ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
		*r = _aligned((t_u8 *)dest, (t_u8 *)src, i);
		if (r)
			return (0);
		if(((t_u8 *)dest + *i)[0] != ((t_u8 *)src + *i)[0])
			return (((t_u8 *)dest + *i)[0] - ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
		*r = _aligned((t_u8 *)dest, (t_u8 *)src, i);
	}
	if (*n >= 1 && !*r) {
		if(((t_u8 *)dest + *i)[0] != ((t_u8 *)src + *i)[0])
			return (((t_u8 *)dest + *i)[0] - ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
		*r = _aligned((t_u8 *)dest, (t_u8 *)src, i);
	}
	return (0);
}

/*
 * Function: lv_memcmp
 * -------------------
 * Compares the first `n` bytes of the memory areas `dest` and `src`.
 * The comparison is performed byte by byte, from left to right.
 *
 * Parameters:
 * dest - A pointer to the first memory area.
 * src  - A pointer to the second memory area.
 * n    - The number of bytes to compare.
 *
 * Returns:
 * An integer less than, equal to, or greater than zero if the first
 * `n` bytes of `dest` are found, respectively, to be less than, to match,
 * or be greater than the first `n` bytes of `src`.
 *
 * Notes:
 * - This function is optimized to handle unaligned memory access initially,
 * then transitions to word-sized comparisons (32-bit, 64-bit, 128-bit)
 * if the pointers become aligned, and finally falls back to byte-wise
 * comparison for any remaining bytes.
 * - It uses helper functions `_alinger`, `_cmp_u8`, `_cmp_u32`, `_cmp_u64`,
 * and `_cmp_u128` for efficient comparison.
 */

ssize_t	lv_memcmp(void *__restrict__ dest,
	const void *__restrict__ src, size_t n)
{
	size_t	i;
	t_u8	r;
	ssize_t	r2;
	ssize_t	r3;

	if ((!dest && !src) || n == 0 || dest == src)
		return (0);
	if ((!dest && src) || (!src && dest))
		return (-1);
	i = 0;
	r = _aligned((t_u8 *)dest, (t_u8 *)src, &i);
	r3 = 0;
	r2 = _alinger(dest, src, &n, &r, &i);
	if (r2 < 0)
		return (r2);
	if (n >= sizeof(t_u128) * 2 && r == 128)
		r3 = _cmp_u128((t_u8 *)dest, (t_u8 *)src, &n, &i);
	else if (n >= sizeof(t_u64) * 2 && r >= 64)
		r3 = _cmp_u64((t_u8 *)dest, (t_u8 *)src, &n, &i);
	else if (n >= sizeof(t_u32) * 2 && r >= 32)
		r3 = _cmp_u32((t_u8 *)dest, (t_u8 *)src, &n, &i);
	if (n > 0 && r3 == 0)
		r3 = _cmp_u8((t_u8 *)dest, (t_u8 *)src, &n, &i);
	return (r3);
}
