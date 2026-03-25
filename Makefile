# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcuello <mcuello@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 21:31:23 by mcuello           #+#    #+#              #
#    Updated: 2026/03/25 15:24:27 by mcuello          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

SRC			= main.c \
			  extension_rules.c \
			  fd_reader.c \
			  fd_parser.c \
			  fd_parser_aux.c \
			  fd_map_parser.c \
			  map_validations.c \
			  set_game.c \
			  aux.c \
			  get_next_line.c \
			  get_next_line_utils.c \
			  mlx_init_game.c \
			  loop_func.c \
			  hook.c \
			  ray_casting.c \
			  ray_collision.c \

OBJ			= $(SRC:.c=.o)

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g -Iinclude -Imlx -Ilibft

MLX_DIR		= MLX

MLX_LIB		= $(MLX_DIR)/build/libmlx42.a

MLX_FLAGS	= -LMLX/build -lmlx42 -ldl -lglfw -pthread -lm

MLX_INC		= -I$(MLX_DIR)/include

LIB_DIR		= libft

LIB		= $(LIB_DIR)/libft.a

all: $(LIB) $(MLX_LIB) $(NAME)

$(LIB):
	@make -C $(LIB_DIR) --no-print-directory

$(MLX_LIB):
	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

$(NAME): $(OBJ)
	$(CC) $(OBJ) -L$(LIB_DIR) -lft $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -Ilibft $(MLX_INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_DIR)/build
	make -C $(LIB_DIR) clean --no-print-directory

re: fclean all
