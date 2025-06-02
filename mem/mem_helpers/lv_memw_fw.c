/**
 * lv_memw_fw.c
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
inline void	_copy_u8_fwd(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u8) * 2)
	{
		((t_u8 *)dest + *i)[0] = ((t_u8 *)src + *i)[0];
		*i += sizeof(t_u8);
		((t_u8 *)dest + *i)[0] = ((t_u8 *)src + *i)[0];
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8) * 2;
	}
	while (*n > 0)
	{
		((t_u8 *)dest + *i)[0] = ((t_u8 *)src + *i)[0];
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
	}
}

__attribute__((always_inline))
inline void	_copy_u32_fwd(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u32) * 2)
	{
		((t_u32 *)((t_u8 *)dest + *i))[0] = ((t_u32 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u32);
		((t_u32 *)((t_u8 *)dest + *i))[0] = ((t_u32 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32) * 2;
	}
}

__attribute__((always_inline))
inline void	_copy_u64_fwd(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u64) * 2)
	{
		((t_u64 *)((t_u8 *)dest + *i))[0] = ((t_u64 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u64);
		((t_u64 *)((t_u8 *)dest + *i))[0] = ((t_u64 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64) * 2;
	}
}

__attribute__((always_inline))
inline void	_copy_u128_fwd(void *__restrict__ dest,
	const void *__restrict__ src,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u128) * 2)
	{
		((t_u128 *)((t_u8 *)dest + *i))[0] = ((t_u128 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u128);
		((t_u128 *)((t_u8 *)dest + *i))[0] = ((t_u128 *)((t_u8 *)src + *i))[0];
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128) * 2;
	}
}

__attribute__((always_inline))
inline t_u8	_aligned(const void *__restrict__ dest,
	const void *__restrict__ src, size_t *i)
{
	t_uptr	d;
	t_uptr	s;

	d = (t_uptr)((t_u8 *)dest + *i);
	s = (t_uptr)((t_u8 *)src + *i);
	if (s == *i)
		s = 128;
	if ((d % sizeof(t_u128) == 0)
		&& (s % sizeof(t_u128) == 0))
		return (128);
	if ((d % sizeof(t_u64) == 0)
		&& (s % sizeof(t_u64) == 0))
		return (64);
	if ((d % sizeof(t_u32) == 0)
		&& (s % sizeof(t_u32) == 0))
		return (32);
	return (0);
}
