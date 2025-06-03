/**
* lv_memctz.c
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

__attribute__((always_inline))
__attribute__((hot))
inline t_u8 lv_memctz_u32(t_u32 x)
{
#ifdef __GNUC__
	if (x == 0)
		return (32);
	return ((t_u8)__builtin_ctz(x));
#else
	t_u8 c = 0;
	if (x == 0)
		return (32);
	while (!(x & 0xF)) { c += 4; x >>= 4; }
	while (!(x & 0x3)) { c += 2; x >>= 2; }
	while (!(x & 1)) { c++; x >>= 1; }
	return (c);
#endif
}

__attribute__((always_inline))
__attribute__((hot))
inline t_u8 lv_memctz_u64(t_u64 x)
{
#ifdef __GNUC__
	if (x == 0)
		return (64);
	return ((t_u8)__builtin_ctzll(x));
#else
	t_u8 c = 0;
	if (x == 0)
		return (64);
	while (!(x & 0xF)) { c += 4; x >>= 4; }
	while (!(x & 0x3)) { c += 2; x >>= 2; }
	while (!(x & 1)) { c++; x >>= 1; }
	return (c);
#endif
}

__attribute__((always_inline))
__attribute__((hot))
inline t_u8 lv_memctz_u128(t_u128 x)
{
#if defined(__GNUC__) && defined(__SIZEOF_INT128__)
	if (x == 0)
		return (128);
	return (t_u8)__builtin_ctz(x);
#else
	t_u8 c = 0;
	if (x == 0)
		return (128);
	while (!(x & 0xF)) { c += 4; x >>= 4; }
	while (!(x & 0x3)) { c += 2; x >>= 2; }
	while (!(x & 1)) { c++; x >>= 1; }
	return (c);
#endif
}
