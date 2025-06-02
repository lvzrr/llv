/**
 * vec.h
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

#ifndef VEC_H
# define VEC_H

# include <stddef.h>
# include "structs.h"
# include "map.h"
# include "mem.h"
# include "put.h"

t_vec		lv_vec(size_t alloc_size, size_t sizeof_type);
void		lv_vec_push(t_vec *vec, void *data, size_t len);
void		lv_vec_free(t_vec *vec);
void		lv_vec_reserve(t_vec *v, size_t n);
void		lv_vec_pop(t_vec *__restrict__ v);
void		lv_vec_clear(t_vec *vec);
void		lv_vec_fit(t_vec *vec);
void		lv_vec_insert(t_vec *v, size_t index, void *data,
				size_t len);
void		*lv_vec_peek_last(t_vec *__restrict__ v);
t_u8		lv_vec_popmv(void *__restrict__ dst, t_vec *__restrict__ v);
void		lv_vec_rev(t_vec *v);
#endif
