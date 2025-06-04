/**
 * lv_tolower.c
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
 * function: lv_tolower
 * --------------------
 * converts an uppercase letter to its lowercase equivalent.
 *
 * parameters:
 * c - the character to convert.
 *
 * returns:
 * the lowercase equivalent of `c` if `c` is an uppercase letter; otherwise,
 * `c` is returned unchanged.
 *
 * notes:
 * - assumes ascii character set for conversion.
 */

int	lv_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - ('A' - 'a'));
	return (c);
}
