/**
 * lv_tstr_new.c
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

#include "llv.h"

t_string	lv_tstr_new(ssize_t len)
{
	t_string	out;

	if (len < 0)
	{
		out.len = 0;
		out.alloc_size = 0;
		out.data = NULL;
		return (out);
	}
	out.len = 0;
	out.alloc_size = (size_t) len + 1;
	out.data = lv_calloc(out.alloc_size, 1);
	if (!out.data)
		out = (t_string){0};
	return (out);
}
