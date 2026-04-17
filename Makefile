# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/17 17:55:33 by lucinguy          #+#    #+#              #
#    Updated: 2026/04/17 17:56:44 by lucinguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Check OS name
UNAME = $(shell uname)

MLX_DIR = MiniLibX
MLX_LIB = $(MLX_DIR)/libmlx.a

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRCS = \
	main.c \
	map_checker.c \
	map_checker_utils.c \
	floodfill.c \
	graphics.c \
	map_load.c \
	map_render.c \
	controls.c \
	cleanup.c \
	image_scale.c

OBJS = $(SRCS:.c=.o)

INCS = -I. -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(LIBFT_DIR)/ft_printf -I$(LIBFT_DIR)/gnl

# Change flags and includes location depending on OS
ifeq ($(UNAME), Linux)
	INCS += -I/usr/X11/include
	LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -L/usr/X11/lib -lXext -lX11 -lm -lbsd
else ifeq ($(UNAME), Darwin)
	INCS += -I/opt/X11/include
	LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -L/opt/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
else
	LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus