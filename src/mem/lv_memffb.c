/**
 * lv_memffb.c
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
 * Function: _look4_u8_tmp
 * -----------------------
 * Helper function for `lv_memffb` to handle initial unaligned bytes
 * when searching for a specific byte `x` in a memory region. It attempts
 * to find `x` byte-by-byte (two at a time) until alignment is achieved or `n` is exhausted.
 *
 * Parameters:
 * ptr - A pointer to the memory region to search. Assumed to be aligned to 8 for `__builtin_assume_aligned`.
 * x   - The 8-bit value (byte) to search for.
 * n   - A pointer to the remaining number of bytes to search. This value is decremented.
 * i   - A pointer to the current index within the buffer. This value is incremented.
 * r   - A pointer to a `t_u8` that will store the alignment status from `_aligned`.
 *
 * Returns:
 * A pointer to the first occurrence of `x` if found in the unaligned section,
 * otherwise NULL.
 *
 * Notes:
 * - This function is `always_inline` for performance critical paths.
 * - `lk` is uninitialized and likely a bug; it should be removed or properly initialized.
 */

LV_INLINE static inline void	*_look4_u8_tmp(void *__restrict__ ptr,
	t_u8 x,
	size_t *__restrict__ n, size_t *__restrict__ i, t_u8 *__restrict__ r)
{
	t_u8	*d;
	int		lk;

	lk = 0;
	d = (t_u8 *) __builtin_assume_aligned(ptr, 8);
	while (*n >= sizeof(t_u8) * 2 && !*r)
	{
		if (*d++ == x)
			return ((t_u8 *)d - sizeof(t_u8) + lk);
		*r = _aligned((t_u8 *)ptr, NULL, i);
		if (r)
			return (NULL);
		if (*d++ == x)
			return ((t_u8 *)d - sizeof(t_u8) + lk);
		*n -= sizeof(t_u8) * 2;
		*i += sizeof(t_u8) * 2;
		*r = _aligned((t_u8 *)ptr, NULL, i);
	}
	return (NULL);
}

/*
 * Function: lv_memffb
 * -------------------
 * Finds the first occurrence of a specific 8-bit value (`x`) within the
 * first `n` bytes of the memory area pointed to by `ptr`. This function
 * uses optimized word-sized comparisons where possible.
 *
 * Parameters:
 * ptr - A pointer to the memory area to search.
 * x   - The 8-bit value (byte) to search for.
 * n   - The number of bytes to examine.
 *
 * Returns:
 * A pointer to the located byte, or a null pointer if the byte is not found.
 *
 * Notes:
 * - This function is designed for performance, starting with an unaligned
 * byte search, then progressing to 128-bit, 64-bit, 32-bit word searches
 * if alignment is achieved, and finally a byte-wise fallback.
 * - It utilizes `__populate
 * to create a mask for word-sized comparisons.
 * - It uses `_look4_u8_tmp`, `_look4_u128_fwd`, `_look4_u64_fwd`,
 * `_look4_u32_fwd`, and `_look4_u8_fwd` for efficient searching.
 */

void	*lv_memffb(const void *__restrict__ ptr,
	t_u8 x, size_t n)
{
	t_u64	mask;
	t_u8	r;
	size_t	i;
	void	*p;

	if (!ptr || n == 0)
		return (NULL);
	mask = __populate(x);
	i = 0;
	p = NULL;
	r = _aligned((t_u8 *)ptr, NULL, &i);
	if (r == 0)
		p = _look4_u8_tmp((t_u8 *)ptr, mask, &n, &i, &r);
	if (n >= sizeof(t_u128) * 2 && r == 128 && !p)
		p = _look4_u128_fwd((t_u8 *)ptr, mask, &n, &i);
	else if (n >= sizeof(t_u64) * 2 && r >= 64 && !p)
		p = _look4_u64_fwd((t_u8 *)ptr, mask, &n, &i);
	else if (n >= sizeof(t_u32) * 2 && r >= 32 && !p)
		p = _look4_u32_fwd((t_u8 *)ptr, (t_u32)mask, &n, &i);
	if (n > 0 && !p)
		p = _look4_u8_fwd((t_u8 *)ptr, x, &n, &i);
	return (p);
}
