/**
 * io.h
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

#ifndef PUT_H
# define PUT_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include "cstr.h"
# include "mem.h"
# include "alloc.h"
# include <stdarg.h>

void			lv_putchar_fd(char c, int fd);
void			lv_putstr_fd(const char *str, int fd);
void			lv_putendl_fd(const char *str, int fd);
void			lv_putnbr_fd(int n, int fd);
char			*get_next_line(int fd);
int				lv_printchar_fd(const char c, int fd);
int				lv_printstr_fd(const char *s, int fd);
void			lv_printnbr_fd(int n, int fd, int *c);
void			lv_printunbr_fd(unsigned int n, int fd, int *c);
void			lv_printptr_fd(unsigned long p, int *c, int fd);
int				lv_printf(const char *fmt, ...);
void			lv_printhex_fd(unsigned int x, const char *set, int *l, int fd);
int				lv_fprintf(int fd, const char *fmt, ...);
#endif
