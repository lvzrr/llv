/**
 * lv_vec_pop.c
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

#include "vec.h"

inline void	lv_vec_pop(t_vec *__restrict__ v)
{
	void	*ptr;

	if (!v || !v->data || v->size == 0)
		return ;
	v->size--;
	ptr = (t_u8 *)v->data + (v->size * v->sizeof_type);
	lv_bzero(ptr, v->sizeof_type);
}
