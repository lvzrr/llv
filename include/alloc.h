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
# include "macros.h"
# include "structs.h"

# ifndef DEF_ALIGN
#  define DEF_ALIGN sizeof(t_u128)
# endif

# ifndef DEFAULT_ARENA_SIZE
#  define DEFAULT_ARENA_SIZE (size_t)(sizeof(size_t) * 2049)
# endif

void			*lv_alloc(size_t size);
void			lv_free(void **ptr);
void			lv_free_array(void ***arr);
void			lv_defer(void *ptr);
void			lv_defer_arr(void ***ptr);
void			*lv_calloc(size_t n, size_t size);
void			*lv_extend(void *ptr, size_t n, size_t size);
void			*lv_extend_zero(void *ptr, size_t n, size_t size);
void			*lv_realloc(void *ptr, size_t n, size_t size);
void			*lv_recalloc(void *ptr, size_t n, size_t size);
void			*lv_arena(size_t size);
void			lv_free_arena(t_arena *arena);
#endif
