/**
 * lv_arena.c
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

#include "alloc.h"

/*
 * Function: lv_init_arena
 * -----------------------
 * Initializes a new memory arena. An arena consists of a 't_arena' structure
 * and a large memory 'pool' from which smaller allocations can be made.
 *
 * Parameters:
 * size - The initial requested allocation size. The pool will be at least
 * twice this size or a default minimum (DEFAULT_ARENA_SIZE), whichever is larger.
 *
 * Returns:
 * A pointer to the newly created 't_arena' structure on success.
 * NULL if memory allocation fails for either the arena structure or its pool.
 */

static t_arena	*lv_init_arena(size_t size)
{
	size_t total_size;

	t_arena *arena = lv_alloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	total_size = LV_MAX(size * 2, DEFAULT_ARENA_SIZE);
	arena->pool = lv_alloc(total_size);
	if (!arena->pool)
		return (lv_free(&(arena->pool)), NULL);
	arena->size = total_size;
	arena->offset = 0;
	arena->next = NULL;
	return (arena);
}

/*
 * Function: lv_manage_req
 * -----------------------
 * Manages allocation requests within a given memory arena. This function handles
 * memory alignment and determines if the current arena has enough space.
 * If not, it attempts to create a new arena and recursively allocates from it.
 *
 * Parameters:
 * arena - A pointer to the current 't_arena' to allocate from.
 * size  - The size of the memory block to allocate in bytes.
 *
 * Returns:
 * A pointer to the aligned allocated memory block on success.
 * NULL if allocation fails (e.g., if a new arena cannot be created).
 *
 * Notes:
 * - Includes space for an internal pointer (sizeof(void*)) at the start of each block.
 * - Ensures allocated memory is aligned to DEF_ALIGN.
 */

static void	*lv_manage_req(t_arena *arena, size_t size)
{
	void	*base;
	void	*aligned;
	size_t	padding;

	base = (t_u8 *)arena->pool + arena->offset + sizeof(void *);
	aligned = (void *)(((t_uptr)base + (DEF_ALIGN - 1)) & ~(DEF_ALIGN - 1));
	padding = (t_u8 *)aligned - (t_u8 *)base;
	if (arena->offset + padding + size > arena->size)
	{
		if (!arena->next)
			arena->next = lv_init_arena(size);
		if (!arena->next)
			return (NULL);
		return (lv_manage_req(arena->next, size));
	}
	arena->offset += padding + size;
	return (aligned);
}

/*
 * Function: lv_arena
 * ------------------
 * The primary interface for allocating memory using the arena allocator.
 * It manages the global arena chain, initializing it on the first call
 * and then directing allocation requests to the current active arena.
 *
 * Parameters:
 * size - The size of the memory block to allocate in bytes.
 *
 * Returns:
 * A pointer to the allocated memory on success.
 * NULL if the requested size is 0 or if allocation fails.
 *
 * Notes:
 * - Uses static variables 'arena' and 'current' to maintain the state
 * of the arena chain across function calls.
 * - Registers a cleanup function (lv_free_arena) with atexit on first call.
 */

void	*lv_arena(size_t size)
{
	static t_arena	*arena;
	static t_arena	*current;

	if (!size)
		return (NULL);
	if (!arena)
	{
		arena = lv_init_arena(size);
		lv_free_arena(arena);
		current = arena;
	}
	if (!arena)
		return (NULL);
	while (current->next)
		current = current->next;
	return (lv_manage_req(current, size));
}

/*
 * Function: lv_free_arena
 * -----------------------
 * Cleans up all memory allocated by the arena allocator. This function is
 * designed to be called automatically at program exit via atexit.
 *
 * Parameters:
 * arena - A pointer to the head of the arena chain (used only on the initial
 * call for setup; will be NULL when called by atexit).
 *
 * Notes:
 * - Uses a static 'store' variable to keep track of the head of the arena chain.
 * - Iterates through all linked arenas, freeing their memory pools and then
 * the arena structures themselves using 'lv_free'.
 * - Uses a temporary 'void *t' to comply with lv_free's 'void **' signature
 * and avoid strict-aliasing warnings, while also nullifying the original
 * pointers.
 */

void    lv_free_arena(t_arena *arena)
{
	static t_arena	*store;
	t_arena			*current_arena;
	t_arena			*next_arena;
	void			*t;

	if (arena && !store)
	{
		store = arena;
		atexit((void (*)(void))lv_free_arena);
		return;
	}
	if (!store)
		return ;
	current_arena = store;
	while (current_arena)
	{
		next_arena = current_arena->next;
		t = current_arena->pool;
		if (current_arena->pool)
			lv_free(&t);
		t = current_arena;
		lv_free(&t);
		current_arena = next_arena;
	}
	store = NULL;
}
