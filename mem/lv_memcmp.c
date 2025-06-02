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

int	lv_memcmp(const void *__restrict__ r1,
	const void *__restrict__ r2, size_t n)
{
	t_u8	*_r1;
	t_u8	*_r2;

	_r1 = (t_u8 *)r1;
	_r2 = (t_u8 *)r2;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*_r1 != *_r2)
			return (*_r1 - *_r2);
		_r1++;
		_r2++;
		n--;
	}
	return (0);
}
