# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schouite <schouite@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/07 13:26:02 by schouite          #+#    #+#              #
#    Updated: 2026/10/07 19:42:51 by schouite         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -Iincludes -Ilibft -Iminilibx-linux
SRC_DIR     = src
OBJ_DIR     = obj

# Bibliothèques externes
LIBFT       = libft/libft.a
MLX         = minilibx-linux/libmlx.a
MLX_FLAGS   = -Lminilibx-linux -lmlx -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lbsd

# Headers dont dépendent les .o (recompile si le header change)
HEADER      = includes/cube3d.h

# Liste de tes sources C
CFILES      = $(SRC_DIR)/main.c \
			  $(SRC_DIR)/parsing/parsing.c \
			  $(SRC_DIR)/parsing/parse_read.c \
			  $(SRC_DIR)/parsing/parse_elements.c \
			  $(SRC_DIR)/parsing/parse_color.c \
			  $(SRC_DIR)/parsing/parse_map.c \
			  $(SRC_DIR)/parsing/parse_walls.c \
			  $(SRC_DIR)/parsing/parse_utils.c \
			  $(SRC_DIR)/raycasting.c \
			  $(SRC_DIR)/render.c \
			  $(SRC_DIR)/render_helper.c \
			  $(SRC_DIR)/init.c \
			  $(SRC_DIR)/init_helper.c \
			  $(SRC_DIR)/utils.c \
			  $(SRC_DIR)/events.c

# Transformation src/%.c -> obj/%.o
OFILES      = $(CFILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C libft

$(MLX):
	@$(MAKE) -C minilibx-linux

$(NAME): $(LIBFT) $(MLX) $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C libft clean
	@$(MAKE) -C minilibx-linux clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
