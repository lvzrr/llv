/**
 * lv_memcpy.c
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
 * Helper function for `lv_memcpy` to handle initial unaligned bytes
 * and attempt to align the pointers for more efficient word-sized copies.
 * It copies bytes two at a time until alignment is achieved.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * src  - A pointer to the source memory region.
 * n    - A pointer to the remaining number of bytes to copy. This value is decremented.
 * r    - A pointer to a `t_u8` that will store the alignment status from `_aligned`.
 *
 * Returns:
 * The number of bytes processed by this function to achieve alignment or exhaust `n`.
 *
 * Notes:
 * - This function is `always_inline` for performance critical paths.
 * - It updates `n` to reflect the bytes processed.
 * - `*r` is set by calls to `_aligned` to indicate if alignment has been achieved.
 */

LV_INLINE inline size_t	_alinger(void *__restrict__ dest,
	const void *__restrict__ src, size_t *n, t_u8 *r)
{
	size_t	x;

	x = 0;
	*r = _aligned((t_u8 *)dest, (t_u8 *)src, &x);
	while (*n >= 2 && !*r)
	{
		((t_u8 *)dest)[x] = ((t_u8 *)src)[x];
		((t_u8 *)dest)[x + 1] = ((t_u8 *)src)[x + 1];
		x += sizeof(t_u8) * 2;
		*n -= sizeof(t_u8) * 2;
		*r = _aligned((t_u8 *)dest, (t_u8 *)src, &x);
	}
	return (x);
}

/*
 * Function: lv_memcpy
 * -------------------
 * Copies `n` bytes from the memory area `src` to the memory area `dest`.
 * The memory areas must not overlap. If they do, `lv_memmove` should be used.
 *
 * Parameters:
 * dest - A pointer to the destination memory area.
 * src  - A pointer to the source memory area.
 * n    - The number of bytes to copy.
 *
 * Returns:
 * A pointer to the destination memory area `dest`.
 *
 * Notes:
 * - This function is marked `hot` indicating it's expected to be called frequently.
 * - It's optimized to handle initial unaligned bytes and then switch to
 * word-sized copies (32-bit, 64-bit, 128-bit) if alignment is achieved,
 * falling back to byte-wise copy for any remaining bytes.
 * - It uses helper functions `_alinger`, `_copy_u8_fwd`, `_copy_u32_fwd`,
 * `_copy_u64_fwd`, and `_copy_u128_fwd` for efficient copying.
 */

LV_SIMD_AVX2 LV_INLINE_HOT inline void	*lv_memcpy(void *__restrict__ dest,
	const void *__restrict__ src, size_t n)
{
	void	*ret;
	size_t	i;
	t_u8	r;

	if ((!dest || !src || dest == src) && n != 0)
		return (NULL);
	r = 0;
	ret = dest;
	i = _alinger(dest, src, &n, &r);
	if (n >= sizeof(t_u128) * 2 && r == 128)
		_copy_u128_fwd((t_u8 *)dest, (t_u8 *)src, &n, &i);
	else if (n >= sizeof(t_u64) * 2 && r >= 64)
		_copy_u64_fwd((t_u8 *)dest, (t_u8 *)src, &n, &i);
	else if (n >= sizeof(t_u32) * 2 && r >= 32)
		_copy_u32_fwd((t_u8 *)dest, (t_u8 *)src, &n, &i);
	if (n > 0)
		_copy_u8_fwd((t_u8 *)dest, (t_u8 *)src, &n, &i);
	return (ret);
}
