/**
 * lv_tstr_from_slice.c
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

t_string lv_tstr_from_slice(char *s, size_t n)
{
	t_string	out;

	if (!s)
	{
		out.len = 0;
		out.alloc_size = 1;
		out.data = lv_alloc(1);
		lv_memset(out.data, 0, 1);
	}
	else
	{
		out.len = n;
		out.alloc_size = out.len + 1;
		out.data = lv_memclone(s, out.len);
		lv_memset(out.data, 0, out.alloc_size);
		if (out.data)
			lv_memcpy(out.data, s, out.len);
	}
	return (out);
}
