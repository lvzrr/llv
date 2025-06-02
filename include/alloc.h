/**
 * alloc.h
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

#ifndef ALLOC_H
# define ALLOC_H

# include <stdlib.h>
# include <sys/types.h>
# include <stdint.h>
# include <stdarg.h>
# include "mem.h"
# include "vec.h"
# include "map.h"

# ifndef USE_GC
#  define USE_GC
# endif

# ifndef LV_DEFER
#  define LV_DEFER __attribute((cleanup(lv_defer)))
# endif

# ifndef LK_VERB
#  define LK_VERB
# endif

extern t_map	*g_table;
extern int		g_gc_critical;

void			*lv_alloc(size_t size);
void			*lv_talloc(size_t size, const char *t);
void			*lv_talloc_raw(size_t size, const char *t, int s);
void			lv_free(void **ptr);
void			lv_defer(void *ptr);
void			lv_gc(void);
void			*lv_calloc(size_t n, size_t size);
void			*lv_extend(void *ptr, size_t n, size_t size);
void			*lv_extend_zero(void *ptr, size_t n, size_t size);
void			*lv_realloc(void *ptr, size_t n, size_t size);
void			*lv_recalloc(void *ptr, size_t n, size_t size);
#endif
