/**
 * lv_gc.c
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
#include "printf.h"

#ifdef USE_GC
static void	lv_gc_debug(void)
{
	t_mem		*mem;
	t_string	*str;
	size_t		i;
	size_t		tombs;

	i = 0;
	tombs = 0;
	while (i < g_table->keys.size)
	{
		mem = &((t_mem *)g_table->values.data)[i];
		str = &((t_string *)g_table->tags.data)[i];
		if (mem->ptr)
			lv_printf("[LVGC] ptr: %p, size: %u, tag: %s\n",
				mem->ptr, mem->size, str->data);
		else
			tombs++;
		i++;
	}
		lv_printf("[LVGC] %u/%u entries manually.\n",
			tombs, g_table->keys.size);
}
#endif

__attribute__((destructor))
void	lv_gc(void)
{
#ifdef USE_GC
	if (g_table)
	{
# ifdef LK_VERB
		lv_gc_debug();
# endif
		lv_map_free(g_table);
		g_table = NULL;
	}
#endif
}
