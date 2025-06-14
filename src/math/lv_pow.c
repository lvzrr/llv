/**
 * lv_pow.c
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
 * Function: lv_pow_u8
 * -------------------
 * Computes the power of a base 'x' raised to an exponent 'n' for unsigned 8-bit integers.
 * This function uses the "exponentiation by squaring" algorithm for efficient computation.
 *
 * Parameters:
 * x - The base (unsigned 8-bit integer).
 * n - The exponent (unsigned 8-bit integer).
 *
 * Returns:
 * The result of x raised to the power of n (x^n) as an unsigned 8-bit integer.
 *
 * Notes:
 * - The algorithm works by repeatedly squaring the base and multiplying by the
 * result only if the corresponding bit in the exponent is set.
 * - This method is more efficient than simple iterative multiplication for large exponents.
 */

t_u8	lv_pow_u8(t_u8 x, t_u8 n)
{
	t_u8	res;

	res = 1;
	while (n) {
		if (n & 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

/*
 * Function: lv_pow_u32
 * --------------------
 * Computes the power of a base 'x' raised to an exponent 'n' for unsigned 32-bit integers.
 * This function uses the "exponentiation by squaring" algorithm for efficient computation.
 *
 * Parameters:
 * x - The base (unsigned 32-bit integer).
 * n - The exponent (unsigned 32-bit integer).
 *
 * Returns:
 * The result of x raised to the power of n (x^n) as an unsigned 32-bit integer.
 *
 * Notes:
 * - The algorithm works by repeatedly squaring the base and multiplying by the
 * result only if the corresponding bit in the exponent is set.
 * - This method is more efficient than simple iterative multiplication for large exponents.
 */

t_u32	lv_pow_u32(t_u32 x, t_u32 n)
{
	t_u32	res;

	res = 1;
	while (n) {
		if (n & 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

/*
 * Function: lv_pow_u64
 * --------------------
 * Computes the power of a base 'x' raised to an exponent 'n' for unsigned 64-bit integers.
 * This function uses the "exponentiation by squaring" algorithm for efficient computation.
 *
 * Parameters:
 * x - The base (unsigned 64-bit integer).
 * n - The exponent (unsigned 64-bit integer).
 *
 * Returns:
 * The result of x raised to the power of n (x^n) as an unsigned 64-bit integer.
 *
 * Notes:
 * - The algorithm works by repeatedly squaring the base and multiplying by the
 * result only if the corresponding bit in the exponent is set.
 * - This method is more efficient than simple iterative multiplication for large exponents.
 */

t_u64	lv_pow_u64(t_u64 x, t_u64 n)
{
	t_u64	res;

	res = 1;
	while (n) {
		if (n & 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

/*
 * Function: lv_pow_u128
 * ---------------------
 * Computes the power of a base 'x' raised to an exponent 'n' for unsigned 128-bit integers.
 * This function uses the "exponentiation by squaring" algorithm for efficient computation.
 *
 * Parameters:
 * x - The base (unsigned 128-bit integer).
 * n - The exponent (unsigned 128-bit integer).
 *
 * Returns:
 * The result of x raised to the power of n (x^n) as an unsigned 128-bit integer.
 *
 * Notes:
 * - The algorithm works by repeatedly squaring the base and multiplying by the
 * result only if the corresponding bit in the exponent is set.
 * - This method is more efficient than simple iterative multiplication for large exponents.
 */

t_u128	lv_pow_u128(t_u128 x, t_u128 n)
{
	t_u128	res;

	res = 1;
	while (n) {
		if (n & 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}
