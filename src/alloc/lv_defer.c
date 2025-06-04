/**
 * lv_defer.c
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
 * Function: lv_defer
 * ------------------
 * Cleanup function used with LV_DEFER attribute.
 *
 * Parameters:
 *   p - pointer to the memory pointer to be freed
 *
 * Returns:
 *   None.
 *
 * Notes:
 *   - Used for scope-based automatic cleanup.
 *   - Frees the memory and sets the pointer to NULL.
 */

void	lv_defer(void *p)
{
	lv_free((void **)p);
}

/*
 * Function: lv_defer_arr
 * ----------------------
 * A wrapper function designed to integrate with a deferred execution mechanism (like LV_DEFER).
 * It facilitates the freeing of an array of dynamically allocated pointers, along with the array itself,
 * when the containing scope exits.
 *
 * Parameters:
 * p    - The address of the pointer to the array of pointers.
 * This is typically the address of a variable holding the base address
 * of the array (e.g., &my_array_of_strings).
 * It's cast to `void **` because `lv_free_arr` expects a `void ***`,
 * and `p` already points to a pointer (`void **`), so `&p` would be `void ***`.
 * Effectively, `p` *is* `arr_ptr_addr` from the perspective of `lv_free_arr`
 * when used in a deferred context where the pointer to the array itself is passed.
 * size - The number of elements (pointers) in the array.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This function relies on `lv_free_arr` to handle the actual deallocation.
 * - It's specifically designed to be called by a macro like `LV_DEFER` to
 * automatically clean up resources.
 * - The `void **p` parameter implicitly expects `p` to be the address of the
 * pointer that points to the array's base address (e.g., `&my_char_array_ptr`).
 * This is why it's cast to `(void ***)p` before being passed to `lv_free_arr`.
 */

void	lv_defer_arr(void ***p)
{
	lv_free_array((void ***)p);
}
