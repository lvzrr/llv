/**
 * lv_tstr_repeat.c
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

void	lv_tstr_repeat(t_string *str, const char *chunk, size_t times)
{
	size_t	chunk_len;
	size_t	total_len;
	char	*new_data;
	size_t	i;

	if (!str || !chunk || !times)
		return ;
	chunk_len = lv_strlen(chunk);
	total_len = chunk_len * times;
	if ((total_len / times) != chunk_len)
		return ;
	if (str->len + total_len + 1 > str->alloc_size)
	{
		new_data = lv_extend_zero(str->data, str->alloc_size,
				str->len + total_len + 1);
		if (!new_data)
			return ;
		str->data = new_data;
		str->alloc_size = str->len + total_len + 1;
	}
	i = 0;
	while (i < times)
		lv_memcpy(str->data + str->len + i++ *chunk_len, chunk, chunk_len);
	str->len += total_len;
	str->data[str->len] = 0;
}
