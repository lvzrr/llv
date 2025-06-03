/**
 * lv_memcmp.c
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
inline ssize_t    _alinger(void *__restrict__ dest,
	const void *__restrict__ src, size_t *n, t_u8 *r,
	size_t *__restrict__ i)
{
	while (*n >= 2 && !*r)
	{
		if(((t_u8 *)dest + *i)[0] != ((t_u8 *)src + *i)[0])
			return (((t_u8 *)dest + *i)[0] - ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
		*r = _aligned((t_u8 *)dest, (t_u8 *)src, i);
		if (r)
			return (0);
		if(((t_u8 *)dest + *i)[0] != ((t_u8 *)src + *i)[0])
			return (((t_u8 *)dest + *i)[0] - ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
		*r = _aligned((t_u8 *)dest, (t_u8 *)src, i);
	}
	if (*n >= 1 && !*r) {
		if(((t_u8 *)dest + *i)[0] != ((t_u8 *)src + *i)[0])
			return (((t_u8 *)dest + *i)[0] - ((t_u8 *)src + *i)[0]);
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
		*r = _aligned((t_u8 *)dest, (t_u8 *)src, i);
	}
	return (0);
}

ssize_t	lv_memcmp(void *__restrict__ dest,
	const void *__restrict__ src, size_t n)
{
	size_t	i;
	t_u8	r;
	ssize_t	r2;
	ssize_t	r3;

	if ((!dest && !src) || n == 0 || dest == src)
		return (0);
	if ((!dest && src) || (!src && dest))
		return (-1);
	i = 0;
	r = _aligned((t_u8 *)dest, (t_u8 *)src, &i);
	r3 = 0;
	r2 = _alinger(dest, src, &n, &r, &i);
	if (r2 < 0)
		return (r2);
	if (n >= sizeof(t_u128) * 2 && r == 128)
		r3 = _cmp_u128((t_u8 *)dest, (t_u8 *)src, &n, &i);
	else if (n >= sizeof(t_u64) * 2 && r >= 64)
		r3 = _cmp_u64((t_u8 *)dest, (t_u8 *)src, &n, &i);
	else if (n >= sizeof(t_u32) * 2 && r >= 32)
		r3 = _cmp_u32((t_u8 *)dest, (t_u8 *)src, &n, &i);
	if (n > 0 && r3 == 0)
		r3 = _cmp_u8((t_u8 *)dest, (t_u8 *)src, &n, &i);
	return (r3);
}
