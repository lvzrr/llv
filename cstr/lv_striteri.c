/**
 * lv_striteri.c
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

#include "cstr.h"

/*
 * Function: lv_striteri
 * ---------------------
 * Applies a function to each character of a string, passing the index
 * and a pointer to the character.
 *
 * Parameters:
 * s - The string to iterate over.
 * f - The function to apply to each character. It takes an unsigned int
 * (index) and a char pointer (to the character) as arguments.
 *
 * Returns:
 * None.
 *
 * Notes:
 * - The function `f` can modify the characters in the string `s`.
 */

void	lv_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &(s[i]));
		i++;
	}
}
