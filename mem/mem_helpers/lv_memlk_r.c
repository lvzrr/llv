/**
 * lv_memlk_r.c
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
inline void	*_look4_u8_fwd_unsafe(void *__restrict__ ptr,
	t_u8 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u8	*d;

	d = (t_u8 *) ptr + *i;
	while (*n >= 2)
	{
		if (*d++ == x)
			return ((t_u8 *)d - 1);
		if (*d++ == x)
			return ((t_u8 *)d - 1);
		(*n) -= 2;
		(*i) += 2;
	}
	while (true)
	{
		if (*d++ == x)
			return ((t_u8 *)d - 1);
		(*n)--;
		(*i)++;
	}
}

__attribute__((always_inline))
inline void	*_look4_u32_fwd(void *__restrict__ ptr,
	t_u32 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u32	*d;
	int		lk;

	d = (t_u32 *) __builtin_assume_aligned(ptr, 4) + *i;
	while (*n >= sizeof(t_u32) * 2)
	{
		lk = _lookup_u32(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u32) + lk);
		lk = _lookup_u32(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u32) + lk);
		*n -= sizeof(t_u32) * 2;
		*i += sizeof(t_u32) * 2;
	}
	while (*n >= sizeof(t_u32))
	{
		lk = _lookup_u32(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u32) + lk);
		*n -= sizeof(t_u32);
		*i += sizeof(t_u32);
	}
	return (NULL);
}

__attribute__((always_inline))
inline void	*_look4_u64_fwd(void *__restrict__ ptr,
	t_u64 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u64	*d;
	int		lk;

	d = (t_u64 *) __builtin_assume_aligned(ptr, 8) + *i;
	while (*n >= sizeof(t_u64) * 2)
	{
		lk = _lookup_u64(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u64) + lk);
		lk = _lookup_u64(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u64) + lk);
		*n -= sizeof(t_u64) * 2;
		*i += sizeof(t_u64) * 2;
	}
	while (*n >= sizeof(t_u64))
	{
		lk = _lookup_u64(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u64) + lk);
		*n -= sizeof(t_u64);
		*i += sizeof(t_u64);
	}
	return (NULL);
}

__attribute__((always_inline))
inline void	*_look4_u128_fwd(void *__restrict__ ptr,
	t_u128 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u128	*d;
	int		lk;
	d = (t_u128 *) __builtin_assume_aligned(ptr, 8) + *i;
	while (*n >= sizeof(t_u128) * 2)
	{
		lk = _lookup_u128(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u128) + lk);
		lk = _lookup_u128(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u128) + lk);
		*n -= sizeof(t_u128) * 2;
		*i += sizeof(t_u128) * 2;
	}
	while (*n >= sizeof(t_u128))
	{
		lk = _lookup_u128(*d++, x);
		if (lk != -1)
			return ((t_u8 *)d - sizeof(t_u128) + lk);
		*n -= sizeof(t_u128);
		*i += sizeof(t_u128);
	}
	return (NULL);
}
