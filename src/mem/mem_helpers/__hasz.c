/**
 * __hasz.c
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
 * Function: __hasz64
 * ------------------
 * Checks if a 64-bit unsigned integer contains a zero byte. This is an
 * optimized way to detect null bytes within a word.
 *
 * Parameters:
 * x - The 64-bit unsigned integer to check.
 *
 * Returns:
 * A non-zero value if a zero byte is found, 0 otherwise.
 *
 * Notes:
 * - This is an inline, hot function for performance.
 * - It leverages bitwise operations for efficient null byte detection.
 */

LV_INLINE_HOT inline int	__hasz64(t_u64 x)
{
    return (((x) -LONES_64) & (~x) & HIGHS_64);
}

/*
 * Function: __hasz128
 * -------------------
 * Checks if a 128-bit unsigned integer contains a zero byte.
 *
 * Parameters:
 * x - The 128-bit unsigned integer to check.
 *
 * Returns:
 * A non-zero value if a zero byte is found, 0 otherwise.
 *
 * Notes:
 * - This is an inline, hot function for performance.
 * - It splits the 128-bit integer into two 64-bit parts and uses `__hasz64`
 * on each part.
 */

#include "mem.h"

LV_INLINE_HOT inline int	__hasz128(t_u128 x)
{
    t_u64 low_part;
	t_u64 high_part;


	high_part = (t_u64)(x >> 64);
	low_part = (t_u64)x;
    return (__hasz64(low_part) || __hasz64(high_part));
}
