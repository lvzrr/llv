/**
 * ctype.h
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

#ifndef CTYPE_H
# define CTYPE_H

int				lv_isalpha(int c);
int				lv_isdigit(int c);
int				lv_isalnum(int c);
int				lv_isascii(int c);
int				lv_isprint(int c);
t_u8			lv_isspace(int c);
#endif
