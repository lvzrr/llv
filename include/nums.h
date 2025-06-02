/**
 * nums.h
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

#ifndef NUMS_H
# define NUMS_H
# include <unistd.h>
# include <stdlib.h>

int				lv_atoi(const char *str);
char			*lv_itoa(int n);
int				lv_atoi_base(char *str, char *base, int base_len);
char			*lv_itoa_base(int n, char *base);
char			*lv_utoa_base(size_t n, char *base);
#endif
