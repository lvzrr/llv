/**
 * lv_memst_w.c
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

#include "mem.h"

/*
 * Function: _write_u8_fwd
 * -----------------------
 * Fills a memory region with a specific 8-bit value (byte) in a forward direction.
 * This is a helper for `memset`-like operations for unaligned or small remaining data.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * x    - The 8-bit value (byte) to write.
 * n    - A pointer to the remaining number of bytes to write.
 * i    - A pointer to the current index within the buffer.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2 bytes where possible, then single bytes.
 */

LV_INLINE  inline void	_write_u8_fwd(void *__restrict__ dest,
	t_u8 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	while (*n >= sizeof(t_u8) * 2)
	{
		((t_u8 *)dest + *i)[0] = x;
		*i += sizeof(t_u8);
		((t_u8 *)dest + *i)[0] = x;
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8) * 2;
	}
	while (*n > 0)
	{
		((t_u8 *)dest + *i)[0] = x;
		*i += sizeof(t_u8);
		*n -= sizeof(t_u8);
	}
}

/*
 * Function: _write_u32_fwd
 * ------------------------
 * Fills a memory region with a specific 32-bit value in a forward direction.
 * This is a helper for `memset`-like operations, optimized for 32-bit writes.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * x    - The 32-bit value to write.
 * n    - A pointer to the remaining number of bytes to write.
 * i    - A pointer to the current index within the buffer.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 32-bit words where possible, then single words.
 * - Assumes appropriate alignment for 32-bit access.
 */

LV_SIMD_AVX2 LV_INLINE inline void	_write_u32_fwd(void *__restrict__ dest,
	t_u32 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	dest = __builtin_assume_aligned(dest, 32);
	_mm_prefetch(dest, _MM_HINT_T0);
#ifdef __AVX2__
	const __m256i val256 = _mm256_set1_epi32((int)x);
	while (*n >= sizeof(t_u32) * 8)
	{
		_mm256_store_si256((__m256i *)((t_u8 *)dest + *i), val256);
		*i += sizeof(t_u32) * 8;
		*n -= sizeof(t_u32) * 8;
	}
#endif
#ifdef __SSE2__
	const __m128i val128 = _mm_set1_epi32((int)x);
	while (*n >= sizeof(t_u32) * 4)
	{
		_mm_store_si128((__m128i *)((t_u8 *)dest + *i), val128);
		*i += sizeof(t_u32) * 4;
		*n -= sizeof(t_u32) * 4;
	}
#endif
	while (*n >= sizeof(t_u32) * 2)
	{
		((t_u32 *)((t_u8 *)dest + *i))[0] = x;
		*i += sizeof(t_u32);
		((t_u32 *)((t_u8 *)dest + *i))[0] = x;
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32) * 2;
	}
	while (*n >= sizeof(t_u32))
	{
		((t_u32 *)((t_u8 *)dest + *i))[0] = x;
		*i += sizeof(t_u32);
		*n -= sizeof(t_u32);
	}
}

/*
 * Function: _write_u64_fwd
 * ------------------------
 * Fills a memory region with a specific 64-bit value in a forward direction.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * x    - The 64-bit value to write.
 * n    - A pointer to the remaining number of bytes to write.
 * i    - A pointer to the current index within the buffer.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 64-bit words where possible, then single words.
 * - Assumes appropriate alignment for 64-bit access.
 */

LV_SIMD_AVX2 LV_INLINE inline void	_write_u64_fwd(void *__restrict__ dest,
	t_u64 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	dest = __builtin_assume_aligned(dest, 64);
	_mm_prefetch(dest, _MM_HINT_T0);
#ifdef __AVX512F__
	const __m512i val512 = _mm512_set1_epi64((long long)x);
	while (*n >= sizeof(t_u64) * 4)
	{
		_mm512_store_si512((__m512i *)((t_u8 *)dest + *i), val512);
		*i += sizeof(t_u64) * 4;
		*n -= sizeof(t_u64) * 4;
	}
#endif
#ifdef __AVX2__
	const __m256i val256 = _mm256_set1_epi64x((long long)x);
	while (*n >= sizeof(t_u64) * 2)
	{
		_mm256_store_si256((__m256i *)((t_u8 *)dest + *i), val256);
		*i += sizeof(t_u64) * 2;
		*n -= sizeof(t_u64) * 2;
	}
#endif
#ifdef __SSE2__
	const __m128i val128 = _mm_set1_epi64x((long long)x);
	while (*n >= sizeof(t_u64))
	{
		_mm_store_si128((__m128i *)((t_u8 *)dest + *i), val128);
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64);
	}
#else
	while (*n >= sizeof(t_u64))
	{
		((t_u64 *)((t_u8 *)dest + *i))[0] = x;
		*i += sizeof(t_u64);
		*n -= sizeof(t_u64);
	}
#endif
}

/*
 * Function: _write_u128_fwd
 * -------------------------
 * Fills a memory region with a specific 128-bit value in a forward direction.
 *
 * Parameters:
 * dest - A pointer to the destination memory region.
 * x    - The 128-bit value to write.
 * n    - A pointer to the remaining number of bytes to write.
 * i    - A pointer to the current index within the buffer.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - This is an inline helper function.
 * - It processes memory in chunks of 2x 128-bit words where possible, then single words.
 * - Assumes appropriate alignment for 128-bit access.
 */

LV_SIMD_AVX2 LV_INLINE inline void	_write_u128_fwd(void *__restrict__ dest,
	t_u128 x,
	size_t *__restrict__ n, size_t *__restrict__ i)
{
	dest = __builtin_assume_aligned(dest, 128);
	_mm_prefetch(dest, _MM_HINT_T0);
#ifdef __AVX512F__
	const __m512i val512 = _mm512_set1_epi64((long long)x);
	while (*n >= sizeof(t_u128) * 2)
	{
		_mm512_store_si512((__m512i *)((t_u8 *)dest + *i), val512);
		*i += sizeof(t_u128) * 2;
		*n -= sizeof(t_u128) * 2;
	}
#endif
#ifdef __AVX2__
	const __m256i val256 = _mm256_set1_epi64x((long long)x);
	while (*n >= sizeof(t_u128))
	{
		_mm256_store_si256((__m256i *)((t_u8 *)dest + *i), val256);
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128);
	}
#else
	while (*n >= sizeof(t_u128))
	{
		((t_u128 *)((t_u8 *)dest + *i))[0] = x;
		*i += sizeof(t_u128);
		*n -= sizeof(t_u128);
	}
#endif
}
