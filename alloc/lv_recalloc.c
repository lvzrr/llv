/**
 * lv_recalloc.c
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

void	*lv_recalloc(void *ptr, size_t n, size_t size)
{
	void	*p;

	if (!size)
		return (lv_free(&ptr), NULL);
	if (!ptr)
		return (lv_calloc(size, 1));
	p = lv_calloc(size, 1);
	if (!p)
		return (lv_free(&ptr), NULL);
	if (size < n)
		n = size;
	lv_memmove(p, ptr, n);
	if (ptr)
		lv_free(&ptr);
	return (p);
}
