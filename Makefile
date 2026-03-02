# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/02 11:22:10 by lucinguy          #+#    #+#              #
#    Updated: 2026/03/02 18:12:39 by lucinguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := so_long
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
RM      := rm -f

# Detect OS (macOS or Linux)
UNAME   := $(shell uname)

# MiniLibX library configuration
MLX_DIR := MiniLibx
MLX_LIB := $(MLX_DIR)/libmlx.a

# Include paths: project root, MiniLibX, and X11 headers (for XQuartz on macOS)
INCS    := -I. -I$(MLX_DIR) -I/usr/X11/include

# Link flags: MiniLibX library, X11 libraries (XExt, X11), and math library
LFLAGS  := -L$(MLX_DIR) -lmlx -L/usr/X11/lib -lXext -lX11 -lm

# On Linux: also link against libbsd for BSD utility functions
ifeq ($(UNAME), Linux)
	LFLAGS += -lbsd
endif

SRCS := main.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# Build MiniLibX library if it doesn't exist
# Suppress all output from lib compilation ("> /dev/null 2>&1" = both stderr and stdout)
$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1

# Link executable: depends on object files and MiniLibX library
$(NAME): $(OBJS) $(MLX_LIB)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)
	@echo "✓ $(NAME) compiled successfully!"

# Remove object files and clean MiniLibX build
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean

# Full clean: remove objects, executable, and clean MiniLibX
fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus