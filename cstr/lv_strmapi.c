/**
 * lv_strmapi.c
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
 * Function: lv_strmapi
 * --------------------
 * Applies a function to each character of a string to create a new string.
 *
 * Parameters:
 * str - The source string.
 * f   - The function to apply. It takes an unsigned int (index) and a char
 * (character) as arguments and returns the transformed character.
 *
 * Returns:
 * A pointer to the newly allocated string with the transformed characters on success.
 * NULL if the input string is NULL or if memory allocation fails.
 *
 * Notes:
 * - The caller is responsible for freeing the allocated memory.
 * - The original string `str` is not modified.
 */

char	*lv_strmapi(char const *str, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*out;

	if (!str)
		return (NULL);
	out = lv_alloc(lv_strlen(str) + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (str[i])
	{
		out[i] = f(i, str[i]);
		i++;
	}
	out[i] = 0;
	return (out);
}
