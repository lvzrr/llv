/**
 * lv_strnstr.c
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

char	*lv_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	if (!*needle)
		return ((char *)haystack);
	if (!*haystack)
		return (NULL);
	while (needle[l])
		l++;
	while (haystack[i] && (i + l) <= n)
	{
		if (!lv_strncmp(&(haystack[i]), needle, l))
			return ((char *)(&(haystack[i])));
		i++;
	}
	return ((void *) 0);
}
