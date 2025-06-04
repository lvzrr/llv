/**
 * lv_memtake.c
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

#include "vec.h"

/*
 * Function: lv_memtake
 * --------------------
 * Copies `len` bytes from the memory area `src` to `dst`, and then
 * zeroes out the original `src` memory area. This function is useful
 * for "moving" data by copying and then clearing the source,
 * especially for sensitive information.
 *
 * Parameters:
 * dst - A pointer to the destination memory area.
 * src - A pointer to the source memory area.
 * len - The number of bytes to copy and then zero out.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This function combines the functionality of `lv_memcpy` and `lv_bzero`.
 * - It handles null pointers or zero length by doing nothing.
 */

void	lv_memtake(void *__restrict__ dst,
	void *__restrict__ src, size_t len)
{
	if (!dst || !src || !len)
		return ;
	lv_memcpy(dst, src, len);
	lv_bzero(src, len);
}
