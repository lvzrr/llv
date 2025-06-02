/**
 * lv_memset.c
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
static inline t_u128	populate(int y)
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
inline size_t	_alinger(void *__restrict__ dest,
	t_u8 o, size_t *n, t_u8 *r)
{
	size_t	x;

	x = 0;
	while (*n >= 2 && !*r)
	{
		((t_u8 *)dest)[x] = o;
		((t_u8 *)dest)[x + 1] = o;
		x += sizeof(t_u8) * 2;
		*n -= sizeof(t_u8) * 2;
		*r = _aligned((t_u8 *)dest, NULL, &x);
	}
	return (x);
}

void	*lv_memset(void *__restrict__ dest, int c, size_t n)
{
	size_t	i;
	t_u8	r;
	t_u64	x;

	if ((!dest) && n != 0)
		return (NULL);
	r = 0;
	x = populate(c);
	i = _alinger(dest, (t_u8)x, &n, &r);
	if (n >= sizeof(t_u128) * 2 && r == 128)
		_write_u128_fwd((t_u8 *)dest, x, &n, &i);
	else if (n >= sizeof(t_u64) * 2 && r == 64)
		_write_u64_fwd((t_u8 *)dest, (t_u64)x, &n, &i);
	else if (n >= sizeof(t_u32) * 2 && r == 32)
		_write_u32_fwd((t_u8 *)dest, (t_u32)x, &n, &i);
	if (n > 0)
		_write_u8_fwd((t_u8 *)dest, (t_u8)x, &n, &i);
	return (dest);
}
