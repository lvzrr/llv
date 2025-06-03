/**
 * lv_memswap.c
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

#ifndef BUFFER_SIZE
 # define BUFFER_SIZE 256
#endif

/*
 * Function: lv_memswap_dyn
 * ------------------------
 * Swaps the contents of two memory regions (`p1` and `p2`) of `len` bytes
 * using a dynamically allocated temporary buffer. This is used when `len`
 * exceeds a predefined `BUFFER_SIZE` or when a stack-allocated buffer is
 * not feasible.
 *
 * Parameters:
 * p1  - A pointer to the first memory region.
 * p2  - A pointer to the second memory region.
 * len - The number of bytes to swap.
 *
 * Returns:
 * 1 on success, 0 if `p1`, `p2`, or `len` is invalid, or if memory allocation fails.
 *
 * Notes:
 * - This function is `always_inline` for performance.
 * - It allocates memory using `lv_alloc` and ensures it's freed using `LV_DEFER`.
 * - It performs the swap by copying `p1` to buffer, `p2` to `p1`, then buffer to `p2`.
 */

__attribute__((always_inline))
inline static t_u8	lv_memswap_dyn(void *__restrict__ p1,
	void *__restrict__ p2, size_t len)
{
	LV_DEFER t_u8	*buffer;

	if (!p1 || !p2 || !len)
		return (0);
	buffer = lv_alloc(len * sizeof(t_u8));
	if (!buffer)
		return (0);
	lv_memcpy(buffer, p1, len);
	lv_memcpy(p1, p2, len);
	lv_memcpy(p2, buffer, len);
	return (1);
}

/*
 * Function: lv_memswap_bounded
 * ----------------------------
 * Swaps the contents of two memory regions (`p1` and `p2`) of `len` bytes
 * using a fixed-size, stack-allocated buffer. This is used when `len` is
 * within the `BUFFER_SIZE` limit, avoiding dynamic memory allocation overhead.
 *
 * Parameters:
 * p1  - A pointer to the first memory region.
 * p2  - A pointer to the second memory region.
 * len - The number of bytes to swap.
 *
 * Returns:
 * 1 on success, 0 if `p1`, `p2`, or `len` is invalid.
 *
 * Notes:
 * - This function is `always_inline` for performance.
 * - It uses `LV_ALIGN(128)` to ensure the buffer is 128-byte aligned for
 * potential vectorized operations.
 * - It performs the swap by copying `p1` to buffer, `p2` to `p1`, then buffer to `p2`.
 */

__attribute__((always_inline))
inline static t_u8	lv_memswap_bounded(void *__restrict__ p1,
	void *__restrict__ p2, size_t len)
{
	LV_ALIGN(128) t_u8 buffer[BUFFER_SIZE];

	if (!p1 || !p2 || !len)
		return (0);
	lv_memcpy(buffer, p1, len);
	lv_memcpy(p1, p2, len);
	lv_memcpy(p2, buffer, len);
	return (1);
}

/*
 * Function: lv_memswap
 * --------------------
 * Swaps the contents of two memory regions (`p1` and `p2`) of `len` bytes.
 * This function acts as a dispatcher, choosing between a stack-allocated
 * buffer (`lv_memswap_bounded`) or a dynamically allocated buffer (`lv_memswap_dyn`)
 * based on the `len` and `BUFFER_SIZE`.
 *
 * Parameters:
 * p1  - A pointer to the first memory region.
 * p2  - A pointer to the second memory region.
 * len - The number of bytes to swap.
 *
 * Returns:
 * 1 on successful swap, 0 otherwise (e.g., invalid pointers, zero length,
 * or memory allocation failure for dynamic swap).
 *
 * Notes:
 * - `BUFFER_SIZE` is a preprocessor macro that determines the threshold
 * for using a stack-allocated vs. heap-allocated buffer.
 */

t_u8	lv_memswap(void *__restrict__ p1,
	void *__restrict__ p2, size_t len)
{
	if (len <= BUFFER_SIZE)
		return (lv_memswap_bounded(p1, p2, len));
	else
		return (lv_memswap_dyn(p1, p2, len));
}

/*
 * Function: lv_memswap_extern
 * ---------------------------
 * Swaps the contents of two memory regions (`p1` and `p2`) of `len` bytes
 * using an externally provided temporary `buffer`. This function is useful
 * when the caller wants to manage the temporary buffer's allocation.
 *
 * Parameters:
 * p1     - A pointer to the first memory region.
 * p2     - A pointer to the second memory region.
 * len    - The number of bytes to swap.
 * buffer - A pointer to an externally provided temporary buffer of at least `len` bytes.
 *
 * Returns:
 * 1 on success, 0 if `p1`, `p2`, `len` is invalid.
 *
 * Notes:
 * - This function is `always_inline` for performance.
 * - The caller is responsible for ensuring `buffer` is valid and has sufficient size.
 * - It performs the swap by copying `p1` to buffer, `p2` to `p1`, then buffer to `p2`.
 */

__attribute__((always_inline))
inline t_u8	lv_memswap_extern(void *__restrict__ p1,
	void *__restrict__ p2, size_t len,
	void *__restrict__ buffer)
{
	if (!p1 || !p2 || !len)
		return (0);
	lv_memcpy(buffer, p1, len);
	lv_memcpy(p1, p2, len);
	lv_memcpy(p2, buffer, len);
	return (1);
}
