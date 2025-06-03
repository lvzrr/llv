/**
 * lv_strncmp.c
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
 * Function: lv_strncmp
 * --------------------
 * Compares up to `n` characters of two null-terminated strings lexicographically.
 *
 * Parameters:
 * s1 - The first string to compare.
 * s2 - The second string to compare.
 * n  - The maximum number of characters to compare.
 *
 * Returns:
 * An integer less than, equal to, or greater than zero if the first `n`
 * characters of `s1` are found, respectively, to be less than, to match,
 * or be greater than the first `n` characters of `s2`.
 *
 * Notes:
 * - Internally uses `lv_memcmp` for the comparison.
 */

int	lv_strncmp(const char *s1, const char *s2, size_t n)
{
	return (lv_memcmp((void *)s1, (void *)s2, n));
}
