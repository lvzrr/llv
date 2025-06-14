/**
 * math.h
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

#ifndef MATH_H
# define MATH_H

# include "mem.h"

float			lv_q_sqrt(float x);
float			lv_q_sqrt_round(float number, t_u8 n);
float			lv_q_sqrt_fround(float number);
float			lv_roundf(float x, t_u8 n);
float			lv_floorf(float x);
float			lv_ceilf(float x);
t_u128			lv_pow_u128(t_u128 x, t_u128 n);
t_u64			lv_pow_u64(t_u64 x, t_u64 n);
t_u32			lv_pow_u32(t_u32 x, t_u32 n);
t_u8			lv_pow_u8(t_u8 x, t_u8 n);
int				lv_ipow(int x, t_u64 n);
long long		lv_lpow(long long x, t_u64 n);
float			lv_fpow(float x, t_u64 n);
double			lv_dpow(double x, t_u64 n);
float			lv_roundff(float x);
#endif
