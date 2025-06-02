/**
 * lv_vec_peek_last.c
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

__attribute__((always_inline))
__attribute__((hot))
inline void	*lv_vec_peek_last(t_vec *__restrict__ v)
{
	if (!v)
		return (NULL);
	if (v->size == 0)
		return (v->data);
	return ((t_u8 *)v->data + (v->size - 1)
		* v->sizeof_type);
}
