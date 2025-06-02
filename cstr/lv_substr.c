/**
 * lv_substr.c
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

char	*lv_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	j;
	char			*out;

	if (!s)
		return (NULL);
	if (len == 0 || start >= lv_strlen(s))
		return (lv_strdup(""));
	if (len > lv_strlen(s) - start)
		len = lv_strlen(s) - start;
	out = lv_alloc(len + 1);
	if (!out)
		return (NULL);
	j = 0;
	while (j < len && s[start])
		out[j++] = s[start++];
	out[j] = 0;
	return (out);
}
