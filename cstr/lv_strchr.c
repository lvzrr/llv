/**
 * lv_strchr.c
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

char	*lv_strchr(const char *haystack, int needle)
{
	unsigned int	i;

	i = 0;
	while (haystack[i] && haystack[i] != (char)needle)
		i++;
	if (haystack[i] == 0 && (char)needle != 0)
		return ((void *) 0);
	return ((char *)(haystack + i));
}
