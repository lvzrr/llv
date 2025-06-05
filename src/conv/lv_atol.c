/**
 * lv_atol.c
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
 * Function: lv_atol
 * -----------------
 * Converts a string to a long integer (ssize_t), similar to the standard `atol` function.
 * It handles leading whitespace, an optional sign ('+' or '-'), and digits.
 *
 * Parameters:
 * str - The input string to convert.
 *
 * Returns:
 * The long integer value represented by the string.
 */

ssize_t	lv_atol(const char *str)
{
	ssize_t		out;
	int			neg;
	size_t		i;

	out = 0;
	i = 0;
	neg = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		out = out * 10 + (str[i++] - '0');
	return (out * neg);
}
