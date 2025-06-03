/**
 * lv_memcm_r.c
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
inline ssize_t	_cmp_u8(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u8) * 2)
	{
		if (((t_u8 *)dest + *i)[0]
			!= ((t_u8 *)src + *i)[0])
			return (ssize_t)(((t_u8 *)dest + *i)[0]
				- ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
		if (((t_u8 *)dest + *i)[0]
			!= ((t_u8 *)src + *i)[0])
			return (ssize_t)(((t_u8 *)dest + *i)[0]
				- ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
	}
	while (*n >= sizeof(t_u8))
	{
		if (((t_u8 *)dest + *i)[0]
			!= ((t_u8 *)src + *i)[0])
			return (ssize_t)(((t_u8 *)dest + *i)[0]
				- ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
	}
	return (0);
}

__attribute__((always_inline))
inline ssize_t    _cmp_u32(void *__restrict__ dest,
    const void * __restrict__ src,
    size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u32) * 2)
	{
		if (((t_u32 *)((t_u8 *)dest + *i))[0]
			!= ((t_u32 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u32 *)((t_u8 *)dest + *i))[0]
				- ((t_u32 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32);
		if (((t_u32 *)((t_u8 *)dest + *i))[0]
			!= ((t_u32 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u32 *)((t_u8 *)dest + *i))[0]
				- ((t_u32 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32);
	}
	while (*n >= sizeof(t_u32))
	{
		if (((t_u32 *)((t_u8 *)dest + *i))[0]
			!= ((t_u32 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u32 *)((t_u8 *)dest + *i))[0]
				- ((t_u32 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32);
	}
	return (0);
}

__attribute__((always_inline))
inline ssize_t	_cmp_u64(void *__restrict__ dest,
	const void * __restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u64) * 2)
	{
		if (((t_u64 *)((t_u8 *)dest + *i))[0]
			!= ((t_u64 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u64 *)((t_u8 *)dest + *i))[0]
				- ((t_u64 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64);
		if (((t_u64 *)((t_u8 *)dest + *i))[0]
			!= ((t_u64 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u64 *)((t_u8 *)dest + *i))[0]
				- ((t_u64 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64);
	}
	while (*n >= sizeof(t_u64))
	{
		if (((t_u64 *)((t_u8 *)dest + *i))[0]
			!= ((t_u64 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u64 *)((t_u8 *)dest + *i))[0]
				- ((t_u64 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64);
	}
	return (0);
}

__attribute__((always_inline))
inline ssize_t	_cmp_u128(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u128) * 2)
	{
		if (((t_u128 *)((t_u8 *)dest + *i))[0]
			!= ((t_u128 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u128 *)((t_u8 *)dest + *i))[0]
				- ((t_u128 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128);
		if (((t_u128 *)((t_u8 *)dest + *i))[0]
			!= ((t_u128 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u128 *)((t_u8 *)dest + *i))[0]
				- ((t_u128 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128);
	}
	while (*n >= sizeof(t_u128))
	{
		if (((t_u128 *)((t_u8 *)dest + *i))[0]
			!= ((t_u128 *)((t_u8 *)src + *i))[0])
			return (ssize_t)(((t_u128 *)((t_u8 *)dest + *i))[0]
				- ((t_u128 *)((t_u8 *)src + *i))[0]);
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128);
	}
	return (0);
}
