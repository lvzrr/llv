/**
 * lv_free.c
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

#include "alloc.h"

void	lv_free(void	**ptr)
{
	t_mem	*mem;

	if (!ptr || !*ptr)
		return ;
#ifdef USE_GC
		mem = lv_map_lookup(g_table,
				(size_t)(*ptr) >> 4);
		if (mem && !mem->freed && mem->ptr)
		{
			free(mem->ptr);
			mem->freed = 1;
			mem->ptr = NULL;
			mem->size = 0;
		}
		else if (!mem || mem->ptr != *ptr)
			free(*ptr);
#else
	free(*ptr);
	*ptr = NULL;
#endif
}
