/**
 * lv_strdup.c
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

#include "cstr.h"

/*
 * Function: lv_strdup
 * -------------------
 * Duplicates a null-terminated string. A new memory block is allocated
 * and the content of the source string is copied into it.
 *
 * Parameters:
 * str - The null-terminated string to duplicate.
 *
 * Returns:
 * A pointer to the newly allocated and duplicated string on success.
 * NULL if the input string is NULL or if memory allocation fails.
 *
 * Notes:
 * - The caller is responsible for freeing the allocated memory.
 * - Uses `lv_strlen` to determine the length and `lv_alloc` for memory.
 */

char	*lv_strdup(const char *str)
{
	size_t	n;

	if (!str)
		return (NULL);
	n = lv_strlen(str);
	return (lv_memclone((void *)str, n + 1));
}
