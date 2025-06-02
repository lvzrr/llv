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
__attribute__((hot))
inline int	_lookup_u32(t_u32 word, t_u32 mask)
{
	t_u32	diff;
	t_u32	t;

	diff = word ^ mask;
	t = (diff - 0x01010101U) & ~diff & 0x80808080U;
	if (!t)
		return (-1);
	return (lv_memctz_u32(t) >> 3);
}

__attribute__((always_inline))
__attribute__((hot))
inline int	_lookup_u64(t_u64 word, t_u64 mask)
{
	t_u64	diff;
	t_u64	t;

	diff = word ^ mask;
	t = (diff - 0x0101010101010101ULL)
		& ~diff & 0x8080808080808080ULL;
	if (!t)
		return (-1);
	return (lv_memctz_u64(t) >> 3);
}

__attribute__((always_inline))
__attribute__((hot))
inline int _lookup_u128(t_u128 word, t_u128 mask)
{
	t_u128	diff;
	t_u128	t;

	diff = word ^ mask;
	t = (diff - (t_u128)0x0101010101010101ULL)
		& ~diff & (t_u128)0x8080808080808080ULL;
	if (!t)
		return (-1);
	return lv_memctz_u128(t) >> 3;
}

__attribute__((always_inline))
__attribute__((hot))
inline void	*_look4_u8_fwd(void *__restrict__ ptr,
	t_u8 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u8	*d;

	d = (t_u8 *) ptr;
	while (*n >= 2)
	{
		if (*d++ == x)
			return ((t_u8 *)d - 1);
		if (*d++ == x)
			return ((t_u8 *)d - 1);
		(*n) -= 2;
		(*i) += 2;
	}
	while (*n > 0)
	{
		if (*d++ == x)
			return ((t_u8 *)d - 1);
		(*n)--;
		(*i)++;
	}
	return (NULL);
}

__attribute__((always_inline))
__attribute__((hot))
inline void	*_look4_u32_fwd(void *__restrict__ ptr,
	t_u32 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u32	*d;
	int		lk;

	d = (t_u32 *) __builtin_assume_aligned(ptr, 4);
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
	return (NULL);
}

__attribute__((always_inline))
__attribute__((hot))
inline void	*_look4_u64_fwd(void *__restrict__ ptr,
	t_u64 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u64	*d;
	int		lk;

	d = (t_u64 *) __builtin_assume_aligned(ptr, 8);
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
	return (NULL);
}

__attribute__((always_inline))
__attribute__((hot))
inline void	*_look4_u128_fwd(void *__restrict__ ptr,
	t_u128 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	t_u128	*d;
	int		lk;

	d = (t_u128 *) __builtin_assume_aligned(ptr, 8);
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
	return (NULL);
}
