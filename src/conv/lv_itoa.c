/**
 * lv_itoa.c
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
 * Counts the number of digits required to represent an integer 'n' in base 10.
 * This includes a potential sign character for negative numbers.
 *
 * Parameters:
 * n - The integer number.
 *
 * Returns:
 * The number of characters needed to represent 'n' as a string.
 */

static unsigned int	count(int n)
{
	unsigned int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

/*
 * Function: _abs
 * --------------
 * Calculates the absolute value of an integer.
 * This is a helper function typically used internally.
 *
 * Parameters:
 * x - The integer number.
 *
 * Returns:
 * The absolute value of 'x'.
 */

static int	_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

/*
 * Function: lv_itoa
 * -----------------
 * Converts an integer 'n' to its string representation in base 10.
 * The function allocates memory for the resulting string, which must be freed by the caller.
 *
 * Parameters:
 * n - The integer to convert.
 *
 * Returns:
 * A newly allocated string containing the decimal representation of the number on success.
 * NULL if memory allocation fails.
 *
 * Notes:
 * - This function handles negative numbers by prepending a '-' sign.
 * - The `lv_alloc` function is assumed to be provided elsewhere.
 */

char	*lv_itoa(int n)
{
	int				neg;
	char			*out;
	unsigned int	cc;

	cc = count(n);
	neg = 1;
	out = lv_alloc(cc + 1);
	if (!out)
		return (NULL);
	if (n < 0)
	{
		out[0] = '-';
		neg = -1;
	}
	out[cc] = 0;
	while (cc > 0 || n != 0)
	{
		if (neg == -1 && cc == 1)
			break ;
		out[--cc] = '0' + (char)(_abs(n % 10));
		n /= 10;
	}
	return (out);
}
