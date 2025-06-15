/**
 * lv_atof.c
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

#include "conv.h"

/*
 * Function: __eat_decimal
 * -----------------
 * Parses the decimal part of a floating-point number from a string.
 * It reads digits after the decimal point and converts them into their
 * fractional float representation.
 *
 * Parameters:
 * s - A pointer to the string starting from the decimal part.
 *
 * Returns:
 * The floating-point value of the decimal part.
 */

static inline float	__eat_decimal(const char *s)
{
	float	c;
	float	out;

	c = 0.1f;
	out = 0;
	while (*s && (*s >= '0' && *s <= '9'))
	{
		out += c * (*s++ - '0');
		c *= 0.1f;
	}
	return (out);
}

/*
 * Function: lv_atof
 * -----------------
 * Converts a string to a floating-point number (float), similar to the
 * standard `atof` function. It handles an optional sign ('+' or '-'),
 * the integer part, and the decimal part.
 *
 * Parameters:
 * s - The input string to convert.
 *
 * Returns:
 * The float value represented by the string. Returns 0 if the input
 * string is NULL.
 */

float	lv_atof(const char *s)
{
	int		neg;
	float	out;

	if (!s)
		return (0);
	out = 0;
	neg = 1;
	if (*s == '-')
	{
		neg = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s && *s != '.' && (*s >= '0' && *s <= '9'))
		out = (out * 10) + (*s++ - '0');
	if (*s == '.')
		s++;
	out += __eat_decimal(s);
	return (out * neg);
}
