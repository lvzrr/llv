/**
 * lv_strlen.c
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

#include "cstr.h"

/*
 * Function: lv_strlen
 * -------------------
 * Calculates the length of a null-terminated string. This implementation
 * attempts to optimize the length calculation by checking multiple bytes
 * at a time using 64-bit word comparisons.
 *
 * Parameters:
 * str - The null-terminated string.
 *
 * Returns:
 * The number of characters in `str`, excluding the null terminator.
 *
 * Notes:
 * - Handles unaligned initial bytes.
 * - Uses `t_u64` and `t_u128` for word-sized processing.
 * - Relies on `__hasz64` macro to efficiently check for null bytes
 * within a 64-bit word.
 */

#include <stdio.h>

size_t	lv_strlen(const char *str)
{
	const char	*a;
	ssize_t		lk;
	const t_u64	*w_64;

	if (!str)
		return (0);
	a = str;
	while ((t_uptr)str % sizeof(t_u64))
	{
		if (*str == '\0')
			return (str - a);
		str++;
	}
	w_64 = (const t_u64 *)str;
	while (true)
	{
		lk = _lookup_u64(w_64[0], __populate(0));
		if (lk != -1)
		{
			str = (const char *)w_64 + lk;
			break ;
		}
		w_64++;
	}
	return (str - a);
}
