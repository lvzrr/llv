/**
 * lv_tstr_fit.c
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

void	lv_tstr_fit(t_string *str)
{
	char	*new;

	if (!str || str->len + 1 == str->alloc_size)
		return ;
	new = lv_realloc(str->data, str->alloc_size, str->len + 1);
	if (!new)
		return ;
	str->data = new;
	str->alloc_size = str->len + 1;
}
