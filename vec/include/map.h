/**
 * map.h
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

#ifndef MAP_H
# define MAP_H

# ifndef MAP_SIZE
#  define MAP_SIZE 256
# endif

# include "structs.h"
# include <sys/types.h>
# include <stdarg.h>
# include "vec.h"
# include "tstr.h"
# include "mem.h"

t_map			*lv_map_init(void);
int				lv_map_insert(void *ptr, size_t size, t_map *map, ...);
t_mem			*lv_map_lookup(t_map *map, size_t key);
void			lv_map_free(t_map *map);
#endif
