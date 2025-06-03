/**
 * lv_memset.c
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
 * This creates a mask where every byte is `y`, useful for fast memory
 * setting in word-sized operations.
 *
 * Parameters:
 * y - The integer value (character) to repeat, cast to `t_u128`.
 *
 * Returns:
 * A 128-bit unsigned integer with `y` replicated across all its bytes.
 *
 * Notes:
 * - This function is `always_inline` for performance.
 * - It works by successive left shifts and OR operations to fill the `t_u128`.
 */

__attribute__((always_inline))
static inline t_u128	populate(int y)
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
 * Function: _alinger
 * ------------------
 * Helper function for `lv_memset` to handle initial unaligned bytes
 * and attempt to align the destination pointer for more efficient word-sized writes.
 * It writes the specified byte `o` two at a time until alignment is achieved.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * o    - The 8-bit value (byte) to write.
 * n    - A pointer to the remaining number of bytes to write. This value is decremented.
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

__attribute__((always_inline))
inline size_t	_alinger(void *__restrict__ dest,
	t_u8 o, size_t *n, t_u8 *r)
{
	size_t	x;

	x = 0;
	while (*n >= 2 && !*r)
	{
		((t_u8 *)dest)[x] = o;
		((t_u8 *)dest)[x + 1] = o;
		x += sizeof(t_u8) * 2;
		*n -= sizeof(t_u8) * 2;
		*r = _aligned((t_u8 *)dest, NULL, &x);
	}
	return (x);
}

/*
 * Function: lv_memset
 * -------------------
 * Fills the first `n` bytes of the memory area pointed to by `dest` with
 * the constant byte `c`.
 *
 * Parameters:
 * dest - A pointer to the destination memory area.
 * c    - The integer value to fill the memory with, interpreted as an `unsigned char`.
 * n    - The number of bytes to set.
 *
 * Returns:
 * A pointer to the destination memory area `dest`.
 *
 * Notes:
 * - This function is optimized to handle initial unaligned bytes and then
 * transition to word-sized writes (32-bit, 64-bit, 128-bit) if alignment
 * is achieved, falling back to byte-wise write for any remaining bytes.
 * - It uses `populate` to create a repeated byte mask for word-sized writes.
 * - It uses helper functions `_alinger`, `_write_u8_fwd`, `_write_u32_fwd`,
 * `_write_u64_fwd`, and `_write_u128_fwd` for efficient filling.
 */

void	*lv_memset(void *__restrict__ dest, int c, size_t n)
{
	size_t	i;
	t_u8	r;
	t_u64	x;

	if ((!dest) && n != 0)
		return (NULL);
	x = populate(c);
	r = _aligned((t_u8 *)dest, NULL, &x);
	i = _alinger(dest, (t_u8)x, &n, &r);
	if (n >= sizeof(t_u128) * 2 && r == 128)
		_write_u128_fwd((t_u8 *)dest, x, &n, &i);
	else if (n >= sizeof(t_u64) * 2 && r >= 64)
		_write_u64_fwd((t_u8 *)dest, (t_u64)x, &n, &i);
	else if (n >= sizeof(t_u32) * 2 && r >= 32)
		_write_u32_fwd((t_u8 *)dest, (t_u32)x, &n, &i);
	if (n > 0)
		_write_u8_fwd((t_u8 *)dest, (t_u8)x, &n, &i);
	return (dest);
}
