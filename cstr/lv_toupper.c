/**
 * lv_toupper.c
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
 * Function: lv_toupper
 * --------------------
 * Converts a lowercase letter to its uppercase equivalent.
 *
 * Parameters:
 * c - The character to convert.
 *
 * Returns:
 * The uppercase equivalent of `c` if `c` is a lowercase letter; otherwise,
 * `c` is returned unchanged.
 *
 * Notes:
 * - Assumes ASCII character set for conversion.
 */

int	lv_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}
