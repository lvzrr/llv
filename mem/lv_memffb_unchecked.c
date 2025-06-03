/**
 * lv_memffb_unchecked.c
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
static inline t_u128	populate(t_u8 y)
{
	t_u128	x;

	x = (t_u128)y;
	x |= x << 8;
	x |= x << 16;
	x |= x << 32;
	x |= x << 64;
	return (x);
}

__attribute__((always_inline))
static inline void	*_look4_u8_tmp(void *__restrict__ ptr,
	t_u8 x,
	size_t *__restrict__ n, size_t *__restrict__ i, t_u8 *__restrict__ r)
{
	t_u8	*d;
	int		lk;

	d = (t_u8 *) __builtin_assume_aligned(ptr, 8);
	while (*n >= sizeof(t_u8) * 2 && !*r)
	{
		if (*d++ == x)
			return ((t_u8 *)d - sizeof(t_u8) + lk);
		*r = _aligned((t_u8 *)ptr, NULL, i);
		if (r)
			return (NULL);
		if (*d++ == x)
			return ((t_u8 *)d - sizeof(t_u8) + lk);
		*n -= sizeof(t_u8) * 2;
		*i += sizeof(t_u8) * 2;
		*r = _aligned((t_u8 *)ptr, NULL, i);
	}
	return (NULL);
}

__attribute__((always_inline))
static inline void	*_look4_u8_tmp_unsafe(void *__restrict__ ptr,
	t_u8 x,
	size_t *__restrict__ i, t_u8 *__restrict__ r)
{
	t_u8	*d;

	d = (t_u8 *) __builtin_assume_aligned(ptr, 8);
	while (!*r)
	{
		if (*d++ == x)
			return ((t_u8 *)d - sizeof(t_u8));
		*r = _aligned((t_u8 *)ptr, NULL, i);
		if (*r)
			return (NULL);
		if (*d++ == x)
			return ((t_u8 *)d - sizeof(t_u8));
		*i += sizeof(t_u8) * 2;
		*r = _aligned((t_u8 *)ptr, NULL, i);
	}
	return (NULL);
}

void	*lv_memffb_unchecked(const void *__restrict__ ptr,
	t_u8 x)
{
	t_u64	mask;
	t_u8	r;
	size_t	i;
	void	*p;

	if (!ptr)
		return (NULL);
	mask = populate(x);
	i = 0;
	p = 0;
	r = _aligned((t_u8 *)ptr, NULL, &i);
	if (r == 0)
		p = _look4_u8_tmp_unsafe((t_u8 *)ptr, mask, &i, &r);
	if (r == 128 && !p)
		p = _look4_u128_fwd_unsafe((t_u8 *)ptr, mask, &i);
	else if (r >= 64 && !p)
		p = _look4_u64_fwd_unsafe((t_u8 *)ptr, (t_u64)mask, &i);
	else if (r >= 32 && !p)
		p = _look4_u32_fwd_unsafe((t_u8 *)ptr, (t_u32)mask, &i);
	return (p);
}

void	*lv_memffb_b2n_unchecked(const void *__restrict__ ptr,
	t_u8 x, size_t n)
{
	t_u64	mask;
	t_u8	r;
	size_t	i;
	void	*p;

	if (!ptr || n == 0)
		return (NULL);
	mask = populate(x);
	i = 0;
	r = _aligned((t_u8 *)ptr, NULL, &i);
	if (r == 0)
		p = _look4_u8_tmp((t_u8 *)ptr, mask, &n, &i, &r);
	if (n >= sizeof(t_u128) * 2 && r == 128 && !p)
		p = _look4_u128_fwd((t_u8 *)ptr, mask, &n, &i);
	else if (n >= sizeof(t_u64) * 2 && r >= 64 && !p)
		p = _look4_u64_fwd((t_u8 *)ptr, (t_u64)mask, &n, &i);
	else if (n >= sizeof(t_u32) * 2 && r >= 32 && !p)
		p = _look4_u32_fwd((t_u8 *)ptr, (t_u32)mask, &n, &i);
	if (!p)
		p = _look4_u8_fwd_unsafe((t_u8 *)ptr, x, &i);
	return (p);
}
