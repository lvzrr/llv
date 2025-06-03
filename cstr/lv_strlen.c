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

size_t	lv_strlen(const char *str)
{
	const char	*a;
	const t_u64	*w_64;

	a = str;
	w_64 = (const t_u64 *)str;
	while ((t_uptr)str % sizeof(t_u128))
	{
		if (*str == '\0')
			return (str - a);
		str++;
	}
	while (!__hasz64(w_64[0]) && !__hasz64(w_64[1]))
	{
		if (__hasz64(w_64[0]))
			str = (const char *)&w_64[0];
		else if (__hasz64(w_64[0]))
			str = (const char *)&w_64[1];
		if (str == (const char *)&w_64[1]
			|| str == (const char *)&w_64[0])
			break ;
		w_64 += 2;
	}
	while (*str != '\0')
		str++;
	return (str - a);
}
