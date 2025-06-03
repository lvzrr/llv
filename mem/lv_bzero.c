/**
 * lv_bzero.c
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
 * Function: lv_bzero
 * ------------------
 * Sets the first `n` bytes of the memory area pointed to by `ptr` to zero.
 * This function is essentially a wrapper around `lv_memset` with the value `0`.
 *
 * Parameters:
 * ptr - A pointer to the memory area to be zeroed.
 * n   - The number of bytes to zero.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This function is commonly used to clear sensitive data or initialize memory.
 */

void	lv_bzero(void *__restrict__ ptr, size_t n)
{
	lv_memset(ptr, 0, n);
}
