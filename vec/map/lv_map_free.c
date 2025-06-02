/**
 * lv_map_free.c
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

void	lv_map_free(t_map *map)
{
	size_t	size;
	size_t	i;

	if (!map)
		return ;
	size = map->tags.size;
	lv_vec_free(&map->keys);
	i = 0;
	while (i < size)
		lv_free(&(((t_mem *)map->values.data)[i++].ptr));
	i = 0;
	while (i < size)
		lv_tstr_free(&((t_string *)map->tags.data)[i++]);
	lv_vec_free(&map->values);
	lv_vec_free(&map->tags);
	free(map);
}
