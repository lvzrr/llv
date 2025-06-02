/**
 * lv_map_init.c
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

t_map	*lv_map_init(void)
{
	t_map	*map;
	void	*tmp;
	size_t	i;

	map = (t_map *)lv_talloc_raw(sizeof(t_map),
			"(map init)", 1);
	if (!map)
		return (NULL);
	map->keys = lv_vec(MAP_SIZE, sizeof(size_t));
	map->values = lv_vec(MAP_SIZE, sizeof(t_mem));
	map->tags = lv_vec(MAP_SIZE, sizeof(t_string));
	if (!map->keys.data || !map->values.data
		|| !map->tags.data)
	{
		lv_vec_free(&map->keys);
		lv_vec_free(&map->values);
		i = 0;
		while (i < map->tags.size)
			lv_tstr_free(&((t_string *)map->tags.data)[i++]);
		lv_vec_free(&map->tags);
		tmp = (void *)map;
		lv_free(&tmp);
		return (NULL);
	}
	return (map);
}
