/**
 * lv_pow_signed.c
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
 * Function: lv_ipow
 * -----------------
 * Computes the power of a base 'x' raised to an exponent 'n' for signed integers.
 * This function uses the "exponentiation by squaring" algorithm for efficient computation.
 *
 * Parameters:
 * x - The base (signed integer).
 * n - The exponent (unsigned 64-bit integer).
 *
 * Returns:
 * The result of x raised to the power of n (x^n) as a signed integer.
 *
 * Notes:
 * - The algorithm works by repeatedly squaring the base and multiplying by the
 * result only if the corresponding bit in the exponent is set.
 * - This method is more efficient than simple iterative multiplication for large exponents.
 * - For negative bases and odd exponents, the result will be negative. For even exponents,
 * the result will be positive.
 */

int	lv_ipow(int x, t_u64 n)
{
	int	res;

	res = 1;
	while (n)
	{
		if ((n & 1) == 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

/*
 * Function: lv_lpow
 * -----------------
 * Computes the power of a base 'x' raised to an exponent 'n' for signed long long integers.
 * This function uses the "exponentiation by squaring" algorithm for efficient computation.
 *
 * Parameters:
 * x - The base (signed long long integer).
 * n - The exponent (unsigned 64-bit integer).
 *
 * Returns:
 * The result of x raised to the power of n (x^n) as a signed long long integer.
 *
 * Notes:
 * - The algorithm works by repeatedly squaring the base and multiplying by the
 * result only if the corresponding bit in the exponent is set.
 * - This method is more efficient than simple iterative multiplication for large exponents.
 * - For negative bases and odd exponents, the result will be negative. For even exponents,
 * the result will be positive.
 */

long long	lv_lpow(long long x, t_u64 n)
{
	long long	res;

	res = 1;
	while (n)
	{
		if ((n & 1) == 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

/*
 * Function: lv_fpow
 * -----------------
 * Computes the power of a base 'x' raised to an exponent 'n' for single-precision floating-point numbers.
 * This function uses the "exponentiation by squaring" algorithm for efficient computation.
 *
 * Parameters:
 * x - The base (single-precision floating-point number).
 * n - The exponent (unsigned 64-bit integer).
 *
 * Returns:
 * The result of x raised to the power of n (x^n) as a float.
 *
 * Notes:
 * - The algorithm works by repeatedly squaring the base and multiplying by the
 * result only if the corresponding bit in the exponent is set.
 * - This method is more efficient than simple iterative multiplication for large exponents.
 * - Floating-point precision limitations should be considered for very large bases or exponents.
 */

float	lv_fpow(float x, t_u64 n)
{
	float	res;

	res = 1;
	while (n)
	{
		if ((n & 1) == 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

/*
 * Function: lv_dpow
 * -----------------
 * Computes the power of a base 'x' raised to an exponent 'n' for double-precision floating-point numbers.
 * This function uses the "exponentiation by squaring" algorithm for efficient computation.
 *
 * Parameters:
 * x - The base (double-precision floating-point number).
 * n - The exponent (unsigned 64-bit integer).
 *
 * Returns:
 * The result of x raised to the power of n (x^n) as a double.
 *
 * Notes:
 * - The algorithm works by repeatedly squaring the base and multiplying by the
 * result only if the corresponding bit in the exponent is set.
 * - This method is more efficient than simple iterative multiplication for large exponents.
 * - Double-precision offers higher accuracy compared to single-precision floats.
 */

double	lv_dpow(double x, t_u64 n)
{
	double	res;

	res = 1.0f;
	while (n)
	{
		if ((n & 1) == 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}
