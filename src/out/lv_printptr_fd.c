/**
 * lv_printptr_fd.c
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

void	lv_printptr_fd(unsigned long p, int *c, int fd)
{
	if (p == 0)
	{
		write(fd, "(nil)", 5);
		*c += 5;
		return ;
	}
	if (*c == 0)
	{
		write(fd, "0x", 2);
		*c += 2;
	}
	if (p >= 16)
		lv_printptr_fd(p >> 4, c, fd);
	write(fd, &("0123456789abcdef"[p & 0xF]), 1);
	(*c)++;
}
