/**
 * lv_memw_bw.c
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

__attribute__((always_inline))
inline void	_copy_u8_bw(void *__restrict__ dest,
	const void *__restrict__ src, size_t *__restrict__ n,
	size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u8) * 2)
	{
		((t_u8 *)dest + *i - 2)[1] = ((t_u8 *)src + *i - 2)[1];
		*i += sizeof(t_u8);
		((t_u8 *)dest + *i - 2)[0] = ((t_u8 *)src + *i - 2)[0];
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8) * 2;
	}
	while (*n >= sizeof(t_u8) * 2)
	{
		dest = (void *)(((t_u8 *)dest) - sizeof(t_u8));
		src = (void *)(((t_u8 *)src) - sizeof(t_u8));
		((t_u8 *)dest + *i)[0] = ((t_u8 *)src + *i)[0];
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
	}
}

__attribute__((always_inline))
inline void	_copy_u32_bw(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u32) * 2)
	{
		((t_u32 *)((t_u8 *)dest + *i) - 2)[1]
			= ((t_u32 *)((t_u8 *)src + *i) - 2)[1];
		*i += sizeof(t_u32);
		((t_u32 *)((t_u8 *)dest + *i) - 2)[0]
			= ((t_u32 *)((t_u8 *)src + *i)- 2)[0];
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32) * 2;
	}
	while (*n >= sizeof(t_u32))
	{
		((t_u32 *)((t_u8 *)dest + *i) - 2)[1]
			= ((t_u32 *)((t_u8 *)src + *i) - 2)[1];
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32);
	}
}

__attribute__((always_inline))
inline void	_copy_u64_bw(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u64) * 2)
	{
		((t_u64 *)((t_u8 *)dest + *i - 2))[1]
			= ((t_u64 *)((t_u8 *)src + *i - 2))[1];
		*i += sizeof(t_u64);
		((t_u64 *)((t_u8 *)dest + *i) - 2)[0]
			= ((t_u64 *)((t_u8 *)src + *i) - 2)[0];
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64) * 2;
	}
	while (*n >= sizeof(t_u64))
	{
		((t_u64 *)((t_u8 *)dest + *i) - 2)[0]
			= ((t_u64 *)((t_u8 *)src + *i) - 2)[0];
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64);
	}
}

__attribute__((always_inline))
inline void	_copy_u128_bw(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u128) * 2)
	{
		((t_u128 *)((t_u8 *)dest + *i) - 2)[1]
			= ((t_u128 *)((t_u8 *)src + *i) - 2)[1];
		*i += sizeof(t_u128);
		((t_u128 *)((t_u8 *)dest + *i) - 2)[0]
			= ((t_u128 *)((t_u8 *)src + *i) - 2)[0];
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128) * 2;
	}
	while (*n >= sizeof(t_u128))
	{
		((t_u128 *)((t_u8 *)dest + *i) - 2)[0]
			= ((t_u128 *)((t_u8 *)src + *i) - 2)[0];
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128);
	}
}
