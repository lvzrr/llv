#
# Makefile
#
# Copyright (C) 2025 lvzrr <lvzrr@proton.me>
#
# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation, either version
# 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General
# Public License along with this program. If not, see
# <https://www.gnu.org/licenses/>.
#

NAME		:=	liblv.a
CC			:=	cc
GC			?=	0
GC_VRB		?=	0

FLAGS		:=	-Wall -Wextra -Werror -Wno-unused-result -Wstrict-overflow=5 -Wdouble-promotion \
			-Wlogical-op -Wjump-misses-init -Wunsafe-loop-optimizations -Wstrict-aliasing=2 \
			-Wpedantic -Wundef -Wwrite-strings -Wredundant-decls -Wnested-externs -Winline -O3\
			$(if $(filter 1,$(GC)),-DUSE_GC) \
			$(if $(filter 1,$(GC_VRB)),-DLK_VERB)
AR		:=	ar rcs
OBJDIR		:=	build
DIRS		:=	arena map vec tstr cstr alloc in is mem num out lst

SRCS		:=	$(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS		:=	$(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo -e -n "\033[34m==> Compiling...\r\033[0m"
	$(CC) $(FLAGS) -c $< -o $@ -Iinclude

$(NAME): $(OBJS)
	$(AR) $@ $^

install: all
	@sudo cp $(NAME) /usr/local/lib
	@mkdir /usr/local/include/liblv/
	@sudo cp include/* /usr/local/include/liblv/

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean full all

.PHONY: all clean fclean re bonus install full
MAKEFLAGS += --no-print-directory
