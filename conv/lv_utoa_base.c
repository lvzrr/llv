/**
 * lv_utoa_base.c
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

#include "llv.h"

/*
 * Function: count
 * ---------------
 * Counts the number of digits required to represent an unsigned integer 'n'
 * in a given 'blen' (base length).
 *
 * Parameters:
 * n    - The unsigned integer number.
 * blen - The length of the base.
 *
 * Returns:
 * The number of characters needed to represent 'n' in the specified base.
 */

static size_t	count(size_t n, size_t blen)
{
	size_t	c;

	c = 0;
	while (n != 0)
	{
		c++;
		n /= blen;
	}
	return (c);
}

/*
 * Function: lv_lvalidate_base
 * ---------------------------
 * Validates a given base string for use in number conversions.
 * A valid base must:
 * - Have at least 2 unique characters.
 * - Not contain duplicate characters.
 * - Not contain '+' or '-' characters.
 *
 * Parameters:
 * base - The string representing the base to validate.
 *
 * Returns:
 * The length of the base if it's valid.
 * -1 if the base is invalid (e.g., too short, contains duplicates, or contains '+'/' ').
 */

static ssize_t	lv_lvalidate_base(char *base)
{
	char	*ptr;
	ssize_t	l;

	l = lv_strlen(base);
	ptr = base;
	if (l < 2)
		return (-1);
	while (*base)
	{
		ptr = base + 1;
		while (*ptr)
			if (*base == *ptr++
				|| *base == '-'
				|| *base == '+')
				return (-1);
		base++;
	}
	return (l);
}

/*
 * Function: lv_utoa_base
 * ----------------------
 * Converts an unsigned integer 'n' to its string representation in a specified 'base'.
 * The function allocates memory for the resulting string, which must be freed by the caller.
 *
 * Parameters:
 * n    - The unsigned integer to convert.
 * base - The string representing the base (e.g., "0123456789ABCDEF" for hexadecimal).
 *
 * Returns:
 * A newly allocated string containing the unsigned number in the specified base on success.
 * NULL if the base is invalid, memory allocation fails, or for input 0 (which returns "0").
 *
 * Notes:
 * - The function calls `lv_lvalidate_base` to ensure the base is valid.
 * - This function is specifically for unsigned integers.
 * - The `lv_alloc` and `lv_strdup` functions are assumed to be provided elsewhere.
 */

char	*lv_utoa_base(size_t n, char *base)
{
	size_t		blen;
	ssize_t		blen1;
	char		*out;
	size_t		c;

	blen1 = lv_lvalidate_base(base);
	if (blen1 == -1)
		return (NULL);
	blen = (size_t) blen1;
	if (n == 0)
		return (lv_strdup("0"));
	out = lv_alloc(count(n, blen) + 1);
	if (!out)
		return (NULL);
	c = count(n, blen);
	out[c] = 0;
	while (n != 0)
	{
		out[--c] = base[n % blen];
		n /= blen;
	}
	if (c == 1)
		out[--c] = '-';
	return (out);
}
