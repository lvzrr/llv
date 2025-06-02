/**
 * macros.h
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

#ifndef MACROS_H
# define MACROS_H

# ifndef LV_ALIGN
#  define LV_ALIGN(x) __attribute__((aligned(x)))
# endif

# ifndef LV_STRUCT
#define LV_STRUCT(name, align, body, tdef) \
	typedef struct __attribute__((aligned(align))) name body tdef;
# endif

# ifndef LV_DEFER
#  define LV_DEFER __attribute((cleanup(lv_defer)))
# endif

#endif
