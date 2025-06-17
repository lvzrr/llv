/**
 * __populate.c
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


LV_INLINE  inline t_u128	__populate(t_u8 y)
{
	t_u128	x;

	x = (t_u128)y;
	x |= x << 8;
	x |= x << 16;
	x |= x << 32;
	x |= x << 64;
	return (x);
}
