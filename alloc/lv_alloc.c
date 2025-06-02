/**
 * lv_alloc.c
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

t_map	*g_table;
int		g_gc_critical;

void	*lv_alloc(size_t size)
{
	return (lv_talloc(size, NULL));
}

void	*lv_talloc(size_t size, const char *t)
{
	void	*new_alloc;

	if (posix_memalign(&new_alloc, 128, size) != 0)
		return (NULL);
#ifdef USE_GC
	if (!g_gc_critical)
	{
		if (!g_table)
		{
			lv_gc();
			g_table = lv_map_init();
		}
		if (!t || !*t)
			t = "(untagged)";
		lv_map_insert(new_alloc, size, g_table, t);
	}
#endif
	return (new_alloc);
}

void	*lv_talloc_raw(size_t size, const char *t, int skip)
{
	void	*new_alloc;

	if (posix_memalign(&new_alloc, 128, size) != 0)
		return (NULL);
#ifdef USE_GC
	if (!skip && !g_gc_critical)
	{
		if (!t || !*t)
			t = "(untagged)";
		lv_map_insert(new_alloc, size, g_table, t);
	}
#endif
	return (new_alloc);
}
