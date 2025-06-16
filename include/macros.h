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


# ifndef LV_STRUCT
#define LV_STRUCT(name, align, body, tdef) \
	typedef struct __attribute__((aligned(align))) name body tdef;
# endif

# ifndef LV_ALIGN
#  ifdef __GNUC__
#    define LV_ALIGN(x) __attribute__((aligned(x)))
#  else
#    define LV_ALIGN(x)
#  endif
# endif

# ifndef LV_DEFER_ARR
#  ifdef __GNUC__
#    define LV_DEFER_ARR __attribute__((cleanup(lv_defer_arr)))
#  else
#    define LV_DEFER_ARR
#  endif
# endif

# ifndef LV_DEFER_VEC
#  ifdef __GNUC__
#    define LV_DEFER_VEC __attribute__((cleanup(lv_vec_free)))
#  else
#    define LV_DEFER_VEC
#  endif
# endif

# ifndef LV_DEFER
#  ifdef __GNUC__
#    define LV_DEFER __attribute__((cleanup(lv_defer)))
#  else
#    define LV_DEFER
#  endif
# endif

# ifndef LV_GC
#  ifdef __GNUC__
#    define LV_GC __attribute__((destructor(lv_defer)))
#  else
#    define LV_GC
#  endif
# endif

# ifndef LV_INLINE
#  ifdef __GNUC__
#    define LV_INLINE __attribute__((always_inline))
#  else
#    define LV_INLINE
#  endif
# endif

# ifndef LV_HOT
#  ifdef __GNUC__
#    define LV_HOT __attribute__((hot))
#  else
#    define LV_HOT
#  endif
# endif

# ifndef LV_CONST
#  ifdef __GNUC__
#    define LV_CONST __attribute__((const))
#  else
#    define LV_CONST
#  endif
# endif

# ifndef LV_INLINE_HOT
#  ifdef __GNUC__
#    define LV_INLINE_HOT __attribute__((always_inline)) __attribute__((hot))
#  else
#    define LV_INLINE_HOT
#  endif
# endif

// TODO:
// # ifndef LV_FMT_INLINE
// #  define LV_FMT_INLINE(fmt, ...) ({ LV_DEFER char *_s = lv_fmt(fmt, __VA_ARGS__); _s; })
// # endif
//
// # ifndef LV_FMT
// #  define LV_FMT(fmt, ...) (lv_fmt(fmt, __VA_ARGS__))
// # endif

# ifndef LV_UNUSED
#  define LV_UNUSED(x) (void)(x)
# endif

# ifndef LV_MAX
#  define LV_MAX(x, y) ((x) > (y) ? (x) : (y))
# endif

#endif
