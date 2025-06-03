/**
 * lv_memffb_unchecked.c
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
 * Function: populate
 * ------------------
 * Populates a 128-bit unsigned integer with a repeating byte value `y`.
 * This creates a mask where every byte is `y`, useful for fast byte searches
 * in word-sized operations.
 *
 * Parameters:
 * y - The 8-bit value (byte) to repeat.
 *
 * Returns:
 * A 128-bit unsigned integer with `y` replicated across all its bytes.
 *
 * Notes:
 * - This function is `always_inline` for performance.
 * - It works by successive left shifts and OR operations to fill the `t_u128`.
 */

__attribute__((always_inline))
static inline t_u128	populate(t_u8 y)
{
	t_u128	x;

	x = (t_u128)y;
	x |= x << 8;
	x |= x << 16;
	x |= x << 32;
	x |= x << 64;
	return (x);
}

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

__attribute__((always_inline))
static inline void	*_look4_u8_tmp(void *__restrict__ ptr,
	t_u8 x,
	size_t *__restrict__ n, size_t *__restrict__ i, t_u8 *__restrict__ r)
{
	t_u8	*d;
	int		lk;

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
 * Function: _look4_u8_tmp_unsafe
 * ------------------------------
 * Helper function for `lv_memffb_unchecked` to handle initial unaligned bytes
 * when searching for a specific byte `x`. This version is "unsafe" because
 * it assumes the byte will be found and does not have an `n` (size) parameter
 * for bounds checking. It iterates until `_aligned` signals alignment or `x` is found.
 *
 * Parameters:
 * ptr - A pointer to the memory region to search. Assumed to be aligned to 8 for `__builtin_assume_aligned`.
 * x   - The 8-bit value (byte) to search for.
 * i   - A pointer to the current index within the buffer. This value is incremented.
 * r   - A pointer to a `t_u8` that will store the alignment status from `_aligned`.
 *
 * Returns:
 * A pointer to the first occurrence of `x` if found in the unaligned section,
 * otherwise NULL (if `_aligned` unexpectedly returns true without a match).
 *
 * Notes:
 * - This function is `always_inline` for performance critical paths.
 * - It relies on the caller to ensure that `x` will eventually be found within
 * valid memory, as it does not perform explicit bounds checking on `n`.
 */

__attribute__((always_inline))
static inline void	*_look4_u8_tmp_unsafe(void *__restrict__ ptr,
	t_u8 x,
	size_t *__restrict__ i, t_u8 *__restrict__ r)
{
	t_u8	*d;

	d = (t_u8 *) __builtin_assume_aligned(ptr, 8);
	while (!*r)
	{
		if (*d++ == x)
			return ((t_u8 *)d - sizeof(t_u8));
		*r = _aligned((t_u8 *)ptr, NULL, i);
		if (*r)
			return (NULL);
		if (*d++ == x)
			return ((t_u8 *)d - sizeof(t_u8));
		*i += sizeof(t_u8) * 2;
		*r = _aligned((t_u8 *)ptr, NULL, i);
	}
	return (NULL);
}

/*
 * Function: lv_memffb_unchecked
 * -----------------------------
 * Finds the first occurrence of a specific 8-bit value (`x`) within the
 * memory area pointed to by `ptr`. This version is "unchecked" and assumes
 * that `x` will eventually be found, making it suitable for cases where
 * the existence of the character is guaranteed (e.g., null-terminated strings).
 * It uses optimized word-sized comparisons where possible.
 *
 * Parameters:
 * ptr - A pointer to the memory area to search.
 * x   - The 8-bit value (byte) to search for.
 *
 * Returns:
 * A pointer to the located byte. Returns NULL if `ptr` is NULL.
 *
 * Notes:
 * - This function is optimized for speed, assuming the byte will be found.
 * - It utilizes `populate` to create a mask for word-sized comparisons.
 * - It uses `_look4_u8_tmp_unsafe`, `_look4_u128_fwd_unsafe`,
 * `_look4_u64_fwd_unsafe`, and `_look4_u32_fwd_unsafe` for efficient
 * unchecked searching.
 */

void	*lv_memffb_unchecked(const void *__restrict__ ptr,
	t_u8 x)
{
	t_u64	mask;
	t_u8	r;
	size_t	i;
	void	*p;

	if (!ptr)
		return (NULL);
	mask = populate(x);
	i = 0;
	p = 0;
	r = _aligned((t_u8 *)ptr, NULL, &i);
	if (r == 0)
		p = _look4_u8_tmp_unsafe((t_u8 *)ptr, mask, &i, &r);
	if (r == 128 && !p)
		p = _look4_u128_fwd_unsafe((t_u8 *)ptr, mask, &i);
	else if (r >= 64 && !p)
		p = _look4_u64_fwd_unsafe((t_u8 *)ptr, (t_u64)mask, &i);
	else if (r >= 32 && !p)
		p = _look4_u32_fwd_unsafe((t_u8 *)ptr, (t_u32)mask, &i);
	return (p);
}

/*
 * Function: lv_memffb_b2n_unchecked
 * ---------------------------------
 * Finds the first occurrence of a specific 8-bit value (`x`) within the
 * first `n` bytes of the memory area pointed to by `ptr`. This function
 * is a hybrid, handling unaligned portions with bounds checking (`_look4_u8_tmp`)
 * and then potentially moving to unchecked word-sized searches (`_look4_uX_fwd`)
 * or a final unchecked byte-wise search (`_look4_u8_fwd_unsafe`).
 *
 * Parameters:
 * ptr - A pointer to the memory area to search.
 * x   - The 8-bit value (byte) to search for.
 * n   - The number of bytes to examine.
 *
 * Returns:
 * A pointer to the located byte, or a null pointer if the byte is not found
 * within the specified `n` bytes, or if `ptr` is NULL or `n` is 0.
 *
 * Notes:
 * - This function tries to balance performance with a degree of safety.
 * - It utilizes `populate` to create a mask for word-sized comparisons.
 * - The `_look4_u8_fwd_unsafe` at the end suggests that if the byte is not
 * found by aligned word searches within `n`, it will continue searching
 * without explicit bounds, implying an expectation that the byte will
 * eventually be found if `n` was just a "soft" limit or the actual boundary
 * is defined by the presence of `x`. This might be a design choice or a
 * potential source of out-of-bounds access if `x` is truly not present.
 */

void	*lv_memffb_b2n_unchecked(const void *__restrict__ ptr,
	t_u8 x, size_t n)
{
	t_u64	mask;
	t_u8	r;
	size_t	i;
	void	*p;

	if (!ptr || n == 0)
		return (NULL);
	mask = populate(x);
	i = 0;
	r = _aligned((t_u8 *)ptr, NULL, &i);
	if (r == 0)
		p = _look4_u8_tmp((t_u8 *)ptr, mask, &n, &i, &r);
	if (n >= sizeof(t_u128) * 2 && r == 128 && !p)
		p = _look4_u128_fwd((t_u8 *)ptr, mask, &n, &i);
	else if (n >= sizeof(t_u64) * 2 && r >= 64 && !p)
		p = _look4_u64_fwd((t_u8 *)ptr, (t_u64)mask, &n, &i);
	else if (n >= sizeof(t_u32) * 2 && r >= 32 && !p)
		p = _look4_u32_fwd((t_u8 *)ptr, (t_u32)mask, &n, &i);
	if (!p)
		p = _look4_u8_fwd_unsafe((t_u8 *)ptr, x, &i);
	return (p);
}
