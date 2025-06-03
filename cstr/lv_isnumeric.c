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

#include "llv.h"

/*
 * Function: lv_isnumeric
 * --------------------
 * Checks if a string represents a numeric value, allowing for optional leading
 * plus or minus signs and spaces. It returns 1 if at least one digit is found
 * and only contains digits, '+', '-', or ' '. Returns 0 otherwise.
 *
 * Parameters:
 * s - The string to check.
 *
 * Returns:
 * 1 if the string is numeric (contains at least one digit and valid characters),
 * 0 otherwise (including for NULL or empty strings).
 *
 * Notes:
 * - The string must contain at least one digit to be considered numeric.
 * - Spaces, '+' and '-' are allowed but do not count as digits.
 */

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
