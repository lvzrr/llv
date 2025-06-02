/**
 * lv_tstr_insert.c
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

#include "tstr.h"

void	lv_tstr_insert(t_string *str, const char *insert, size_t position)
{
	size_t	insert_len;
	size_t	new_len;

	if (!str || !str->data || !insert || position > str->len)
		return ;
	insert_len = lv_strlen(insert);
	new_len = str->len + insert_len;
	if (new_len + 1 > str->alloc_size)
		lv_tstr_reserve(str, new_len);
	lv_memmove(str->data + position + insert_len,
		str->data + position,
		str->len - position);
	lv_memcpy(str->data + position, insert, insert_len);
	str->len = new_len;
	str->data[str->len] = '\0';
}
