/**
 * lv_memchr.c
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

/*
 * Function: lv_memchr
 * -------------------
 * Scans the initial `n` bytes of the memory area pointed to by `ptr`
 * for the first occurrence of the character `c`. The search is performed
 * byte by byte.
 *
 * Parameters:
 * ptr - A pointer to the memory area to be searched.
 * c   - The character to search for (treated as an unsigned char).
 * n   - The number of bytes to search.
 *
 * Returns:
 * A pointer to the matching byte, or NULL if the character `c` does not
 * occur in the first `n` bytes of the memory area.
 */

void	*lv_memchr(const void *__restrict__ ptr, int c, size_t n)
{
	unsigned int	i;
	t_u8			*p;

	p = (t_u8 *)ptr;
	i = 0;
	while (i < n)
	{
		if (p[i] == (t_u8)c)
			return (p + i);
		i++;
	}
	return ((void *) 0);
}
