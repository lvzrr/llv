/**
 * lv_bitcmp.c
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
inline int _lookup_u32(t_u32 word, t_u32 mask)
{
    t_u32 diff;
    t_u32 t;

	t = (t_u128)0;
    diff = word ^ mask;
    t = (diff - LONES_32) & ~diff & HIGHS_32;
    if (!t)
        return (-1);
    return (lv_memctz_u32(t) >> 3);
}

__attribute__((always_inline))
__attribute__((hot))
inline int _lookup_u64(t_u64 word, t_u64 mask)
{
    t_u64 diff;
    t_u64 t;

	t = (t_u128)0;
    diff = word ^ mask;
    t = (diff - LONES_64) & ~diff & HIGHS_64;
    if (!t)
        return (-1);
    return (lv_memctz_u64(t) >> 3);
}

__attribute__((always_inline))
__attribute__((hot))
inline int _lookup_u128(t_u128 word, t_u128 mask)
{
	int		lkup;
	t_u64	low_word;
	t_u64	high_word;
	t_u64 	low_mask;
	t_u64	high_mask;


	high_mask = (t_u64)(mask >> 64);
	low_mask = (t_u64)mask;
	high_word = (t_u64)(word >> 64);
	low_word = (t_u64)word;
	lkup = _lookup_u64(low_word, low_mask);
	if (lkup != -1)
	{
		return lkup;
	}
	lkup = _lookup_u64(high_word, high_mask);
	if (lkup != -1)
	{
		return 64 + lkup;
	}
	return (-1);
}

__attribute__((always_inline))
inline void	*_look4_u8_fwd(void *__restrict__ ptr,
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
	while (*n > 0)
	{
		if (*d++ == x)
			return ((t_u8 *)d - 1);
		(*n)--;
		(*i)++;
	}
	return (NULL);
}
