/**
 * lv_isnumeric.c
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

#include "liblv.h"

inline t_u8	lv_isnumeric(const char *__restrict__ s)
{
	t_u8	has_digit;

	if (!s || !*s)
		return (0);
	has_digit = 0;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			has_digit = 1;
		else if (*s != '-' && *s != '+' && *s != ' ')
			return (0);
		s++;
	}
	return (has_digit);
}
