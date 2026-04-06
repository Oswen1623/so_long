# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/02 11:22:10 by lucinguy          #+#    #+#              #
#    Updated: 2026/04/06 15:13:36 by lucinguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := so_long
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
RM      := rm -f

# Detect OS (macOS or Linux)
UNAME   := $(shell uname)

# MiniLibX library configuration
MLX_DIR := MiniLibX
MLX_LIB := $(MLX_DIR)/libmlx.a

# Libft library configuration
LIBFT_DIR := libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a

# Include paths: project root, MiniLibX, and X11 headers (for XQuartz on macOS)
INCS    := -I. -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(LIBFT_DIR)/ft_printf -I$(LIBFT_DIR)/gnl -I/usr/X11/include

# Link flags: MiniLibX library, X11 libraries (XExt, X11), and math library
LFLAGS  := -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -L/usr/X11/lib -lXext -lX11 -lm

# On Linux: also link against libbsd for BSD utility functions
ifeq ($(UNAME), Linux)
	LFLAGS += -lbsd
endif

SRCS := main.c \
	map_checker.c \
	map_checker_utils.c \
	floodfill.c \
	graphics.c \

OBJS := $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# Build MiniLibX library if it doesn't exist
# Hide MLX output on success; print errors if MLX build fails
$(MLX_LIB):
	@$(MAKE) -s --no-print-directory -C $(MLX_DIR) > /dev/null 2> .mlx_build.err || { cat .mlx_build.err; $(RM) .mlx_build.err; exit 1; }
	@$(RM) .mlx_build.err

# Build libft library
$(LIBFT_LIB):
	@$(MAKE) -s --no-print-directory -C $(LIBFT_DIR) > /dev/null

# Link executable: depends on object files and MiniLibX library
$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)
	@echo "✓ $(NAME) compiled successfully!"

# Remove object files and clean MiniLibX build
clean:
	$(RM) $(OBJS)
	@$(MAKE) -s --no-print-directory -C $(LIBFT_DIR) clean > /dev/null
	@$(MAKE) -s --no-print-directory -C $(MLX_DIR) clean > /dev/null

# Full clean: remove objects, executable, and clean MiniLibX
fclean: clean
	@$(MAKE) -s --no-print-directory -C $(LIBFT_DIR) fclean > /dev/null
	$(RM) $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus