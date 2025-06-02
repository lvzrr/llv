/**
 * lv_memcpy.c
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
inline size_t	_alinger(void *__restrict__ dest,
	const void *__restrict__ src, size_t *n, t_u8 *r)
{
	size_t	x;

	x = 0;
	while (*n >= 2 && !*r)
	{
		((t_u8 *)dest)[x] = ((t_u8 *)src)[x];
		((t_u8 *)dest)[x + 1] = ((t_u8 *)src)[x + 1];
		x += sizeof(t_u8) * 2;
		*n -= sizeof(t_u8) * 2;
		*r = _aligned((t_u8 *)dest, (t_u8 *)src, &x);
	}
	return (x);
}

__attribute__((hot))
void	*lv_memcpy(void *__restrict__ dest,
	const void *__restrict__ src, size_t n)
{
	void	*ret;
	size_t	i;
	t_u8	r;

	if ((!dest || !src || dest == src) && n != 0)
		return (NULL);
	i = 0;
	r = 0;
	ret = dest;
	i = _alinger(dest, src, &n, &r);
	if (n >= sizeof(t_u128) * 2 && r == 128)
		_copy_u128_fwd((t_u8 *)dest, (t_u8 *)src, &n, &i);
	else if (n >= sizeof(t_u64) * 2 && r >= 64)
		_copy_u64_fwd((t_u8 *)dest, (t_u8 *)src, &n, &i);
	else if (n >= sizeof(t_u32) * 2 && r >= 32)
		_copy_u32_fwd((t_u8 *)dest, (t_u8 *)src, &n, &i);
	if (n > 0)
		_copy_u8_fwd((t_u8 *)dest, (t_u8 *)src, &n, &i);
	return (ret);
}
