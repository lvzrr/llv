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

#define STACKED_SIZE 512

__attribute__((always_inline))
inline static t_u8	lv_memswap_dyn(void *__restrict__ p1,
	void *__restrict__ p2, size_t len)
{
	t_u8	*buffer;

	if (!p1 || !p2 || !len)
		return (0);
	buffer = lv_alloc(len * sizeof(t_u8));
	if (!buffer)
		return (0);
	lv_memcpy(buffer, p1, len);
	lv_memcpy(p1, p2, len);
	lv_memcpy(p2, buffer, len);
	free(buffer);
	return (1);
}

__attribute__((always_inline))
inline static t_u8	lv_memswap_bounded(void *__restrict__ p1,
	void *__restrict__ p2, size_t len)
{
	t_u8 buffer[STACKED_SIZE] __attribute__((aligned(16)));

	if (!p1 || !p2 || !len)
		return (0);
	lv_memcpy(buffer, p1, len);
	lv_memcpy(p1, p2, len);
	lv_memcpy(p2, buffer, len);
	return (1);
}

__attribute__((always_inline))
__attribute__((hot))
inline t_u8	lv_memswap(void *__restrict__ p1,
	void *__restrict__ p2, size_t len)
{
	if (len <= STACKED_SIZE)
		return (lv_memswap_bounded(p1, p2, len));
	else
		return (lv_memswap_dyn(p1, p2, len));
}

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
