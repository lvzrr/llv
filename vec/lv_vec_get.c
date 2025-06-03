/**
 * lv_vec_get.c
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

const void	*lv_vec_get(t_vec *vec, size_t idx)
{
	t_u8	*raw;

	if (!vec || !vec->size || idx > vec->size)
		return (NULL);
	raw = (t_u8 *)vec->data;
	return (raw + (vec->sizeof_type * idx));
}


void	*lv_vec_get_mut(t_vec *vec, size_t idx)
{
	t_u8	*raw;

	if (!vec || !vec->size || idx > vec->size)
		return (NULL);
	raw = (t_u8 *)vec->data;
	return (raw + (vec->sizeof_type * idx));
}


void	*lv_vec_get_clone(t_vec *vec, size_t idx)
{
	t_u8	*raw;

	if (!vec || !vec->size || idx > vec->size)
		return (NULL);
	raw = (t_u8 *)vec->data;
	return(lv_memclone(raw + (vec->sizeof_type * idx),
		vec->sizeof_type));
}
