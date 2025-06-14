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

float	lv_q_sqrt(float x);
float	lv_q_sqrt_round(float number, t_u8 n);
float	lv_roundf(float x, t_u8 n);
float	lv_floorf(float x);
float	lv_ceilf(float x);
#endif
