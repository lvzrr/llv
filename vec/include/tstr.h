/**
 * tstr.h
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

#ifndef TSTR_H
# define TSTR_H
# include <sys/types.h>
# include <stdlib.h>
# include "structs.h"
# include "mem.h"
# include "alloc.h"
# include "cstr.h"

t_string		lv_tstr_from_cstr(const char *str);
char			*lv_tstr_dup_cstr(t_string *str);
t_string		lv_tstr_new(ssize_t len);
void			lv_tstr_pushstr(t_string *str, const char *s);
void			lv_tstr_push(t_string *str, char c);
void			lv_tstr_free(t_string *str);
const char		*lv_tstr_borrow(const t_string *str);
void			lv_tstr_clear(t_string *s);
void			lv_tstr_fit(t_string *str);
ssize_t			lv_tstr_instr(const t_string *h, const char *n);
void			lv_tstr_trim(t_string *str, const char *set);
void			lv_tstr_reserve(t_string *str, size_t n);
char			lv_tstr_pop(t_string *str);
void			lv_tstr_repeat(t_string *str, const char *chunk,
					size_t times);
void			lv_tstr_insert(t_string *str, const char *insert,
					size_t position);
#endif
