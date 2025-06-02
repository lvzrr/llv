/**
 * lv_map_lookup.c
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

t_mem	*lv_map_lookup(t_map *map, size_t key)
{
	size_t	i;
	size_t	*key_ptr;

	if (!map || !map->keys.data || map->keys.size == 0)
		return (NULL);
	i = 0;
	while (i < map->keys.size)
	{
		key_ptr = (size_t *)map->keys.data;
		if (key_ptr[i] == key)
			return ((t_mem *)map->values.data + i);
		i++;
	}
	return (NULL);
}
