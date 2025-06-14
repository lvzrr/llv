/**
 * lv_q_sqrt.c
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
 * Function: lv_q_sqrt
 * -------------------
 * Computes the inverse square root of a single-precision floating-point number
 * using the "Fast Inverse Square Root" algorithm, famously known from Quake III Arena.
 * This algorithm provides a very fast approximation of 1/sqrt(number), which is
 * then used to calculate sqrt(number).
 *
 * Parameters:
 * number - The input floating-point number for which to calculate the square root.
 * Must be non-negative.
 *
 * Returns:
 * The square root of 'number' if 'number' is non-negative.
 * -1 if 'number' is negative, indicating an invalid input for real square root.
 *
 * Notes:
 * - This function relies on specific floating-point representation (IEEE 754)
 * and integer bitwise operations to achieve its speed.
 * - The magic number 0x5f3759df is central to the algorithm's effectiveness,
 * providing an initial approximation of the inverse square root.
 * - It performs two iterations of Newton's method to refine the approximation,
 * balancing accuracy with performance.
 * - The final result is obtained by multiplying the input 'number' by its
 * approximated inverse square root.
 */

float	lv_q_sqrt(float number)
{
	long		i;
	float		x2;
	float		y;
	float		threehalfs;

	if (number < 0)
		return (-1);
	threehalfs = 1.5F;
	x2 = number * 0.5F;
	y  = number;
	lv_memcpy(&i, &y, sizeof(float));
	i  = 0x5f3759df - (i >> 1);
	lv_memcpy(&y, &i, sizeof(float));
	y  = y * (threehalfs - (x2 * y * y));
	y  = y * (threehalfs - (x2 * y * y));
	return (number * y);
}

/*
 * Function: lv_q_sqrt_round
 * --------------------------
 * Computes the square root of a single-precision floating-point number and
 * then rounds the result to a specified number of decimal places. This function
 * uses the "Fast Inverse Square Root" algorithm for an efficient initial
 * approximation of the square root.
 *
 * Parameters:
 * number - The input floating-point number for which to calculate and round
 * the square root. Must be non-negative.
 * n      - The number of decimal places to round the final square root to.
 *
 * Returns:
 * The rounded square root of 'number' if 'number' is non-negative.
 * -1 if 'number' is negative, indicating an invalid input for a real
 * square root.
 *
 * Notes:
 * - This function combines the fast inverse square root approximation with
 * subsequent rounding.
 * - It first checks for negative input, returning -1 as a square root of a
 * negative number is not a real number.
 * - The core of the square root calculation uses bitwise manipulation and a
 * magic number (0x5f3759df) to quickly estimate the inverse square root.
 * - Two iterations of Newton's method are applied to refine this approximation.
 * - Finally, the calculated square root (number * y) is passed to the
 * `lv_roundf` function to round it to `n` decimal places.
 */

float	lv_q_sqrt_round(float number, t_u8 n)
{
	return (lv_roundf(lv_q_sqrt(number), n));
}
