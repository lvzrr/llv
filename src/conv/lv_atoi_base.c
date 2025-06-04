/**
 * lv_atoi_base.c
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
 * Function: lv_check_in_base
 * --------------------------
 * Checks if a given character 'c' exists within the provided 'base' string
 * and returns its position (index) if found.
 *
 * Parameters:
 * c    - The character to search for.
 * base - The string representing the base (e.g., "0123456789" for base 10).
 *
 * Returns:
 * The 0-based index of 'c' in 'base' if found.
 * -1 if 'c' is not found in 'base'.
 */

static int	lv_check_in_base(char c, char *base)
{
	int	pos;

	pos = 0;
	while (*base)
	{
		if (*base++ == c)
			return (pos);
		pos++;
	}
	return (-1);
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
 * Function: lv_atoi_base
 * ----------------------
 * Converts a string 'str' to an integer using a specified 'base'.
 * This function handles leading whitespace, optional signs ('+' or '-'),
 * and converts digits according to the provided base.
 *
 * Parameters:
 * str      - The input string to convert.
 * base     - The string representing the base of the number (e.g., "0123456789ABCDEF" for hexadecimal).
 * base_len - The length of the base. If -1, the base will be validated internally.
 *
 * Returns:
 * The integer representation of the string.
 * 0 if the base is invalid or the string is empty/contains no valid digits.
 *
 * Notes:
 * - This function calls `lv_lvalidate_base` to ensure the base is valid
 * if `base_len` is passed as -1.
 * - It handles standard integer parsing rules including leading whitespace
 * and multiple sign characters (e.g., " --+10" would be 10).
 */

int	lv_atoi_base(char *str, char *base, int base_len)
{
	int				out;
	int				neg;

	if (base_len == -1 || lv_lvalidate_base(base) == -1)
		return (0);
	out = 0;
	neg = 1;
	if (!*str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (lv_check_in_base(*str, base) >= 0)
		out = out * base_len + lv_check_in_base(*str++, base);
	return (out * neg);
}
