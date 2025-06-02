/**
 * lst.h
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

#ifndef LST_H
# define LST_H
# include <sys/types.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*lv_lstnew(void *contents);
int				lv_lstsize(t_list *lst);
void			lv_lstadd_front(t_list **lst, t_list *n);
t_list			*lv_lstlast(t_list *lst);
void			lv_lstadd_back(t_list **lst, t_list *n);
void			lv_lstdelone(t_list *lst, void (*del)(void *));
void			lv_lstclear(t_list **lst, void (*del)(void *));
void			lv_lstiter(t_list *lst, void (*f)(void *));
t_list			*lv_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
#endif
