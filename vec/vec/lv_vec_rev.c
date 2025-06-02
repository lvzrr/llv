/**
 * lv_vec_rev.c
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

void	lv_vec_rev(t_vec *v)
{
	size_t	half;
	size_t	i;

	if (!v || v->size < 2)
		return ;
	half = v->size / 2;
	i = 0;
	while (i < half)
	{
		lv_memswap(
			(t_u8 *)v->data + (v->sizeof_type * i),
			(t_u8 *)v->data + (v->sizeof_type * (v->size - i - 1)),
			v->sizeof_type);
		i++;
	}
}
