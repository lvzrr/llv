/**
 * lv_printhex_fd.c
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

#include "liblv.h"

void	lv_printhex_fd(unsigned int x, const char *set, int *l, int fd)
{
	char	o;

	if (x >= 16)
		lv_printhex_fd(x >> 4, set, l, fd);
	o = set[x & 0xF];
	*l += write(fd, &o, 1);
}
