/**
 * lv_memmove.c
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
 * Function: b
 * -----------
 * Helper function for `lv_memmove` specifically for backward copying.
 * This is invoked when the source and destination memory regions overlap
 * and the destination starts before the source, requiring a copy from
 * the end of the region backward to prevent overwriting uncopied data.
 *
 * Parameters:
 * dest - A pointer to the destination memory region (adjusted for backward copy).
 * src  - A pointer to the source memory region (adjusted for backward copy).
 * n    - The number of bytes to copy.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This function is `always_inline` for performance critical paths.
 * - It handles initial unaligned bytes, then performs backward word-sized
 * copies (128-bit, 64-bit, 32-bit), and finally falls back to byte-wise
 * backward copy for remaining bytes.
 * - The pointers `dest` and `src` are expected to be incremented by `n`
 * by the caller before calling this function, effectively pointing to
 * the end of the respective regions for backward iteration.
 */

LV_INLINE inline void	b(void *__restrict__ dest,
	const void *__restrict__ src, size_t n)
{
	size_t	i;
	t_u8	r;

	i = 0;
	r = _aligned((t_u8 *)dest, (t_u8 *)src, &i);
	while (n >= 2 && !r)
	{
		((t_u8 *)dest)[i] = ((t_u8 *)src)[i];
		((t_u8 *)dest)[i + 1] = ((t_u8 *)src)[i + 1];
		i += sizeof(t_u8) * 2;
		n -= sizeof(t_u8) * 2;
		r = _aligned((t_u8 *)dest, (t_u8 *)src, &i);
	}
	if (n > sizeof(t_u128) * 2 && r == 128)
		_copy_u128_bw((t_u8 *)dest + n, (t_u8 *)src + n, &n, &i);
	else if (n > sizeof(t_u64) * 2 && r >=  64)
		_copy_u64_bw((t_u8 *)dest + n, (t_u8 *)src + n, &n, &i);
	else if (n > sizeof(t_u32) * 32 && r >= 32)
		_copy_u32_bw((t_u8 *)dest + n, (t_u8 *)src + n, &n, &i);
	if (n > 0)
		_copy_u8_bw((t_u8 *)dest + n, (t_u8 *)src + n, &n, &i);
}

/*
 * Function: lv_memmove
 * --------------------
 * Copies `n` bytes from the memory area `src` to the memory area `dest`.
 * The memory areas may overlap.
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
 * - It handles overlapping memory regions by determining if a forward copy
 * (using `lv_memcpy`) or a backward copy (using the internal `b` helper)
 * is necessary.
 * - If `dest` and `src` are the same, or `n` is 0 and `dest` or `src` is NULL,
 * it immediately returns `dest`.
 */

LV_SIMD LV_INLINE_HOT inline void	*lv_memmove(void *__restrict__ dest,
	const void *__restrict__ src, size_t n)
{
	if ((!dest || !src || dest == src) && n != 0)
		return (NULL);
	if ((t_uptr)src < (t_uptr)dest
		&& (t_uptr)src + n >= (t_uptr)dest)
		b(dest, src, n);
	else
		lv_memcpy(dest, src, n);
	return (dest);
}
