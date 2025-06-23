/**
 * printf.h
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

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>

int				lv_printchar_fd(const char c, int fd);
int				lv_printstr_fd(const char *s, int fd);
void			lv_printnbr_fd(int n, int fd, int *c);
void			lv_printunbr_fd(unsigned int n, int fd, int *c);
void			lv_printptr_fd(unsigned long p, int *c, int fd);
int				lv_printf(const char *fmt, ...);
void			lv_printhex_fd(unsigned int x, const char *set, int *l, int fd);
int				lv_fprintf(int fd, const char *fmt, ...);
#endif
