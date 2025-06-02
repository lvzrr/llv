/**
 * lv_strjoin.c
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

char	*lv_strjoin(const char *s1, const char *s2)
{
	size_t			l1;
	size_t			l2;
	size_t			i;
	size_t			j;
	char			*out;

	if (!s1 || !s2)
		return (NULL);
	l1 = lv_strlen(s1);
	l2 = lv_strlen(s2);
	out = malloc(l1 + l2 + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (j < l1)
		out[i++] = s1[j++];
	j = 0;
	while (j < l2)
		out[i++] = s2[j++];
	out[i] = 0;
	return (out);
}
