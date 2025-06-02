/**
 * lv_printf.c
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

static int	is_flag(char c)
{
	return (c == 'c' || c == 'd' || c == 'u'
		|| c == 'p' || c == 'x'
		|| c == 'X' || c == 'u'
		|| c == 's' || c == 'i'
		|| c == '%');
}

static int	numhelper(char c, va_list args)
{
	int	l;

	l = 0;
	if (c == 'u')
		lv_printunbr_fd(va_arg(args, unsigned int), 1, &l);
	else if (c == 'x')
		lv_printhex_fd(va_arg(args, unsigned int),
			"0123456789abcdef", &l, 1);
	else if (c == 'X')
		lv_printhex_fd(va_arg(args, unsigned int),
			"0123456789ABCDEF", &l, 1);
	else
		lv_printnbr_fd(va_arg(args, int), 1, &l);
	return (l);
}

static int	ptrhelper(va_list args)
{
	int				l;
	unsigned long	p;

	p = (unsigned long)va_arg(args, void *);
	l = 0;
	lv_printptr_fd(p, &l, 1);
	return (l);
}

static int	dispatch(char fmt, va_list args)
{
	if (fmt == 'c')
		return (lv_printchar_fd((char)va_arg(args, int), 1));
	else if (fmt == '%')
		return (lv_printchar_fd('%', 1));
	else if (fmt == 's')
		return (lv_printstr_fd(va_arg(args, char *), 1));
	else if (fmt == 'i' || fmt == 'd')
		return (numhelper(fmt, args));
	else if (fmt == 'u')
		return (numhelper(fmt, args));
	else if (fmt == 'p')
		return (ptrhelper(args));
	else if (fmt == 'x')
		return (numhelper(fmt, args));
	else if (fmt == 'X')
		return (numhelper(fmt, args));
	return (0);
}

int	lv_printf(const char *fmt, ...)
{
	va_list		args;
	int			c;

	c = 0;
	va_start(args, fmt);
	if (!fmt || !*fmt)
		return (0);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt && is_flag(*fmt))
				c += dispatch(*fmt, args);
			fmt++;
			continue ;
		}
		write (1, fmt, 1);
		c++;
		fmt++;
	}
	va_end(args);
	return (c);
}
