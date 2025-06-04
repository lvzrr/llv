/**
 * lv_tstr_dup_cstr.c
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

#include "llv.h"

/*
 * Function: lv_tstr_dup_cstr
 * --------------------------
 * Creates a new, dynamically allocated C-style string (null-terminated `char*`)
 * by duplicating the entire allocated memory of a `t_string` object,
 * including any unused capacity and the null terminator.
 *
 * Parameters:
 * str - A pointer to the `t_string` object whose allocated memory will be duplicated.
 *
 * Returns:
 * A newly allocated `char` pointer containing a copy of the `t_string`'s
 * internal buffer (including its null terminator and potentially unused capacity),
 * or NULL if `str` or `str->data` is NULL, or if memory allocation fails.
 *
 * Notes:
 * - This function duplicates the entire allocated block (`str->alloc_size` bytes),
 * not just the active string length (`str->len`). This means it will copy
 * any null terminators or zeroed-out memory that exists beyond the
 * current string content up to the `alloc_size`.
 * - The caller is responsible for freeing the returned C-style string
 * using `lv_free` (or equivalent) when it's no longer needed to prevent memory leaks.
 * - It relies on `lv_memclone` for the actual memory duplication.
 */

char	*lv_tstr_dup_cstr(t_string *str)
{
	if (!str || !str->data)
		return (NULL);
	return (lv_memclone(str->data, str->alloc_size));
}
