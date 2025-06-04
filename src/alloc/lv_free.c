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
 * Frees a memory block allocated by `lv_alloc_align` (or `lv_alloc`)
 * and nullifies the user's pointer to prevent use-after-free bugs.
 *
 * Parameters:
 * ptr - The address of the pointer to the memory block to free.
 * This must be a pointer to the variable holding the address
 * returned by `lv_alloc_align` (e.g., `&my_ptr`).
 *
 * Returns:
 * None.
 *
 * Notes:
 * - Safe to call on `NULL` or already-freed pointers (if the pointer
 * has been correctly set to `NULL` by a previous call).
 * - It retrieves the original `malloc`'d address, which was stored
 * just before the aligned pointer, and then calls the underlying `free`.
 */

void	lv_free(void **ptr)
{
	void	*pp;

	if (!ptr || !*ptr)
		return ;
	pp = *ptr;
	free(((void **)pp)[-1]);
	*ptr = NULL;
}
