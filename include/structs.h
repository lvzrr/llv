/**
 * structs.h
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

#ifndef STRUCTS_H
# define STRUCTS_H

# include <sys/types.h>
# include <stdint.h>
# include "macros.h"

typedef unsigned char	t_u8;
typedef uint32_t		t_u32;
typedef uint64_t		t_u64;
typedef __uint128_t		t_u128;
typedef uintptr_t		t_uptr;

LV_STRUCT(s_string, 32,
{
	size_t	len;
	size_t	alloc_size;
	char	*data;
}, t_string)

LV_STRUCT(s_vec, 32,
{
	size_t	size;
	void	*data;
	size_t	alloc_size;
	size_t	sizeof_type;
}, t_vec)

LV_STRUCT(s_arena, 32,
{
	size_t			size;
	size_t			offset;
	struct s_arena	*next;
	void			*pool;
}, t_arena)

#endif
