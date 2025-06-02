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

/*
 * Function: lv_free
 * -----------------
 * Frees a memory block and nullifies the pointer.
 *
 * Parameters:
 *   ptr - address of the pointer to free
 *
 * Returns:
 *   None.
 *
 * Notes:
 *   - Safe to call on NULL or already-freed pointers.
 *   - Helps prevent use-after-free bugs.
 */

void	lv_free(void	**ptr)
{
	if (!ptr || !*ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}
