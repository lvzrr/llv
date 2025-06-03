/**
 * mem.h
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

#ifndef MEM_H
# define MEM_H
# include <sys/types.h>
# include <stdlib.h>
# include <limits.h>
# include "alloc.h"
# include "structs.h"
# include "macros.h"

# ifndef LONES_64
#  define LONES_64 0x0101010101010101ULL
# endif

# ifndef HIGHS_64
#  define HIGHS_64 0x8080808080808080ULL
# endif

# ifndef ZEROS_64
#  define ZEROS_64 0x0000000000000000ULL
# endif

# define LONES_32  0x01010101U
# define HIGHS_32  0x80808080U

# define LONES_128_CONST (((t_u128)LONES_64 << 64) | LONES_64)
# define HIGHS_128_CONST (((t_u128)HIGHS_64 << 64) | HIGHS_64)
# define ZEROS_128_CONST (((t_u128)ZEROS_64 << 64) | ZEROS_64)
# define ONES_64 ((uint64_t)-1 / UCHAR_MAX)
// Actual api

void			lv_bzero(void *__restrict__ ptr, size_t n);
void			*lv_memset(void *__restrict__ s, int c, size_t n);
void			*lv_memcpy(void *__restrict__ dest,
					const void *__restrict__ src, size_t n);
void			lv_memtake(void *__restrict__ dest,
					void *__restrict__ src, size_t n);
t_u8			lv_memswap(void *__restrict__ p1,
					void *__restrict__ p2, size_t n);
t_u8			lv_memswap_extern(void *__restrict__ p1,
					void *__restrict__ p2, size_t n,
					void *__restrict__ buf);
void			*lv_memmove(void *__restrict__ dest,
					const void *__restrict__ src, size_t n);
void			*lv_memchr(const void *__restrict__ ptr, int c, size_t n);
ssize_t			lv_memcmp(void *__restrict__ dest,
					const void *__restrict__ src, size_t n);
void			*lv_memffb(const void *__restrict__ ptr,
					t_u8 x, size_t n);
void			*lv_memffb_b2n_unchecked(const void *__restrict__ ptr,
					t_u8 x, size_t n);
void			*lv_memclone(void *__restrict__ ptr, size_t size);

/*
 *
 *	HELPERS
 *
 */

// COPY 

void			_copy_u8_fwd(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			_copy_u32_fwd(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			_copy_u64_fwd(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			_copy_u128_fwd(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			_copy_u8_bw(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			_copy_u32_bw(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			_copy_u64_bw(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			_copy_u128_bw(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);

// OVERWRITING

void			_write_u8_fwd(void *__restrict__ dest,
					t_u8 x,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			_write_u32_fwd(void *__restrict__ dest,
					t_u32 x,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			_write_u64_fwd(void *__restrict__ dest,
					t_u64 x,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			_write_u128_fwd(void *__restrict__ dest,
					t_u128 x,
					size_t *__restrict__ n, size_t *__restrict__ i);

// LOOKUP

void			*_look4_u8_fwd(void *__restrict__ ptr,
					t_u8 x,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			*_look4_u32_fwd(void *__restrict__ ptr,
					t_u32 x,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			*_look4_u64_fwd(void *__restrict__ ptr,
					t_u64 x,
					size_t *__restrict__ n, size_t *__restrict__ i);
void			*_look4_u128_fwd(void *__restrict__ ptr,
					t_u128 x,
					size_t *__restrict__ n, size_t *__restrict__ i);

void			*_look4_u8_fwd_unsafe(void *__restrict__ ptr,
					t_u8 x,
					size_t *__restrict__ i);
void			*_look4_u32_fwd_unsafe(void *__restrict__ ptr,
					t_u32 x,
					size_t *__restrict__ i);
void			*_look4_u64_fwd_unsafe(void *__restrict__ ptr,
					t_u64 x,
					size_t *__restrict__ i);
void			*_look4_u128_fwd_unsafe(void *__restrict__ ptr,
					t_u128 x,
					size_t *__restrict__ i);

// CMP

ssize_t			_cmp_u8(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);
ssize_t			_cmp_u32(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);
ssize_t			_cmp_u64(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);
ssize_t			_cmp_u128(void *__restrict__ dest,
					const void *__restrict__ src,
					size_t *__restrict__ n, size_t *__restrict__ i);

// LIL' HELPERS

int				_lookup_u32(t_u32 word, t_u32 mask);
int				_lookup_u64(t_u64 word, t_u64 mask);
int				_lookup_u128(t_u128 word, t_u128 mask);
int				__hasz128(t_u128 x);
int				__hasz64(t_u64 x);

// ALIGNMIENT & CHECKZ
t_u8			lv_memctz_u32(t_u32 x);
t_u8			lv_memctz_u64(t_u64 x);
t_u8			lv_memctz_u128(t_u128 x);
t_u8			_aligned(const void *__restrict__ dest,
					const void *__restrict__ src, size_t *i);
#endif
