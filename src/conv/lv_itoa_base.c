/**
 * lv_itoa_base.c
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
 * Function: _abs
 * --------------
 * Calculates the absolute value of an integer.
 * This is a helper function typically used internally.
 *
 * Parameters:
 * n - The integer number.
 *
 * Returns:
 * The absolute value of 'n' as an unsigned integer.
 */

static unsigned int	_abs(int n)
{
	if (n < 0)
		return ((unsigned int)-n);
	return ((unsigned int)n);
}

/*
 * Function: count
 * ---------------
 * Counts the number of digits required to represent an integer 'n'
 * in a given 'blen' (base length). This includes a potential sign character.
 *
 * Parameters:
 * n    - The integer number.
 * blen - The length of the base.
 *
 * Returns:
 * The number of characters needed to represent 'n' in the specified base.
 */

static size_t	count(int n, int blen)
{
	size_t	c;

	c = 0;
	if (n < 0)
		c++;
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

static int	lv_lvalidate_base(char *base)
{
	char	*ptr;
	int		l;

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
 * Function: lv_itoa_base
 * ----------------------
 * Converts an integer 'n' to its string representation in a specified 'base'.
 * The function allocates memory for the resulting string, which must be freed by the caller.
 *
 * Parameters:
 * n    - The integer to convert.
 * base - The string representing the base (e.g., "0123456789ABCDEF" for hexadecimal).
 *
 * Returns:
 * A newly allocated string containing the number in the specified base on success.
 * NULL if the base is invalid, memory allocation fails, or for input 0 (which returns "0").
 *
 * Notes:
 * - The function calls `lv_lvalidate_base` to ensure the base is valid.
 * - It handles negative numbers by prepending a '-' sign.
 * - The `lv_alloc` and `lv_strdup` functions are assumed to be provided elsewhere.
 */

char	*lv_itoa_base(int n, char *base)
{
	int			blen;
	char		*out;
	size_t		c;

	blen = lv_lvalidate_base(base);
	if (blen == -1)
		return (NULL);
	c = count(n, blen);
	if (n == 0)
		return (lv_strdup("0"));
	out = lv_alloc(c + 1);
	if (!out)
		return (NULL);
	out[c] = 0;
	while (n != 0)
	{
		out[--c] = base[_abs(n % blen)];
		n /= blen;
	}
	if (c == 1)
		out[--c] = '-';
	return (out);
}
