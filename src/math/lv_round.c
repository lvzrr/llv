/**
 * lv_round.c
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

#include "math.h"

/*
 * Function: lv_floorf
 * -------------------
 * Computes the floor of a single-precision floating-point number. The floor
 * of a number is the largest integer less than or equal to that number.
 *
 * Parameters:
 * x - The input floating-point number.
 *
 * Returns:
 * The floor of 'x' as a float.
 *
 * Notes:
 * - This implementation casts the float to an integer and then checks if the
 * integer value is greater than the original float. If it is, it means
 * the original float was negative and had a fractional part, so it
 * subtracts 1 from the integer to get the correct floor.
 */

float	lv_floorf(float x)
{
	long long i;

	i = (long long)x;
	if ((float)i > x)
		return (i - 1);
	return (i);
}

/*
 * Function: lv_ceilf
 * ------------------
 * Computes the ceiling of a single-precision floating-point number. The ceiling
 * of a number is the smallest integer greater than or equal to that number.
 *
 * Parameters:
 * x - The input floating-point number.
 *
 * Returns:
 * The ceiling of 'x' as a float.
 *
 * Notes:
 * - This implementation casts the float to an integer and then checks if the
 * integer value is less than the original float. If it is, it means
 * the original float had a fractional part (positive or negative), so it
 * adds 1 to the integer to get the correct ceiling.
 */

float	lv_ceilf(float x)
{
	long long i;

	i = (long long)x;
	if ((float)i < x)
		return (i + 1);
	return (i);
}

/*
 * Function: lv_roundf
 * -------------------
 * Rounds a single-precision floating-point number to a specified number of
 * decimal places.
 *
 * Parameters:
 * x - The input floating-point number to be rounded.
 * n - The number of decimal places to round to. Clamped to a maximum of 7
 * to avoid potential precision issues with float.
 *
 * Returns:
 * The rounded value of 'x' as a float.
 *
 * Notes:
 * - The function first calculates a power of 10 (p10) corresponding to the
 * desired number of decimal places.
 * - For positive numbers, it multiplies 'x' by p10, adds 0.5, applies the
 * floor function, and then divides by p10. This effectively shifts the
 * decimal point, rounds, and shifts it back.
 * - For negative numbers, it multiplies 'x' by p10, subtracts 0.5, applies the
 * ceiling function, and then divides by p10. This handles rounding for
 * negative numbers correctly.
 * - The maximum value for 'n' (7) is a practical limit for single-precision
 * floats to maintain reasonable accuracy due to their limited precision.
 */

float	lv_roundf(float x, t_u8 n)
{
	float	p10;

	if (n > 7)
		n = 7;
	p10 = 0.1f;
	while (n--)
		p10 *= 10.0f;
	if (x >= 0)
		return (lv_floorf(x * p10 + 0.5f) / p10);
	else
		return (lv_ceilf(x * p10 - 0.5f) / p10);
}

/*
 * Function: lv_roundff
 * --------------------
 * Rounds a single-precision floating-point number to the nearest whole number.
 * This implementation adheres to the common "round half away from zero" rule.
 *
 * Parameters:
 * x - The input floating-point number to be rounded.
 *
 * Returns:
 * The rounded value of 'x' as a float (representing a whole number).
 *
 * Notes:
 * - For positive numbers, 0.5 is added before casting to an integer. This effectively
 * rounds values like 2.5 up to 3.0 (2.5 + 0.5 = 3.0, then cast to int is 3).
 * - For negative numbers, 0.5 is subtracted before casting to an integer. This ensures
 * that values like -2.5 are rounded down to -3.0 (-2.5 - 0.5 = -3.0, then cast to int is -3).
 * This behavior aligns with "round half away from zero," where both 2.5 and -2.5
 * are rounded to 3 and -3 respectively.
 * - This method is generally more robust and predictable for both positive and negative
 * inputs compared to approaches that rely on the modulo operator or simple truncation
 * for negative numbers.
 */

float lv_roundff(float x)
{
	if (x >= 0.0f)
		return (float)((int)(x + 0.5f));
	else
		return (float)((int)(x - 0.5f));
}
