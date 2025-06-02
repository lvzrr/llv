/**
 * lv_map_insert.c
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

#include "map.h"

int	lv_map_insert(void *ptr, size_t size, t_map *map, ...)
{
	va_list		args;
	const char	*t;
	t_string	str;
	t_mem		val;

	if (!ptr || !map)
		return (-1);
	if (lv_map_lookup(map, (size_t)ptr >> 4))
		return (-1);
	val.ptr = ptr;
	val.freed = 0;
	val.size = size;
	va_start(args, map);
	t = va_arg(args, const char *);
	va_end(args);
	if (!t || !*t || lv_strcmp(t, "(cstr->tstr)") == 0)
		str = (t_string){.len = 0, .alloc_size = 0, .data = NULL};
	else
		str = lv_tstr_from_cstr(t);
	lv_vec_push(&map->keys, &(size_t){(size_t)ptr >> 4}, 1);
	lv_vec_push(&map->values, &val, 1);
	lv_vec_push(&map->tags, &str, 1);
	return (1);
}
