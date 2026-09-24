# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schouite <schouite@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/07 13:26:02 by schouite          #+#    #+#              #
#    Updated: 2026/09/24 16:41:06 by schouite         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
CC          = cc
CFLAGS      = 
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
			  $(SRC_DIR)/raycasting.c

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