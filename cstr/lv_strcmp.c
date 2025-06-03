/**
 * lv_strcmp.c
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
 * Function: lv_strcmp
 * -------------------
 * Compares two null-terminated strings lexicographically.
 *
 * Parameters:
 * a - The first string to compare.
 * b - The second string to compare.
 *
 * Returns:
 * An integer less than, equal to, or greater than zero if `a` is found,
 * respectively, to be less than, to match, or be greater than `b`.
 *
 * Notes:
 * - The comparison stops at the first differing character or at the
 * null terminator of either string.
 */

int	lv_strcmp(const char *a, const char *b)
{
	size_t	c;

	c = 0;
	while (a[c] && b[c])
	{
		if (a[c] != b[c])
			return (a[c] - b[c]);
		c++;
	}
	return (a[c] - b[c]);
}
