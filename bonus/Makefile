# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 13:05:52 by adbouras          #+#    #+#              #
#    Updated: 2025/02/03 15:35:21 by adbouras         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BNS_NAME	=	cub3D_bonus
CFLAGS		=	-Wextra -Wall -Werror -fsanitize=address -g
LDFLAGS		=	-fsanitize=address -g
LIBMLX		=	../libraries/MLX42
LIBFT		=	../libraries/libft/libft.a

BNS_HDRS	=	-I ../include -I $(LIBMLX)/include
BNS_INC		=	cub3d_bonus.h get_next_line_bonus.h
LIBS		=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		=	clean_up_bonus.c game_loop_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c init_bonus.c main_bonus.c map_loading_bonus.c parse_map_bonus.c player_movment_bonus.c \
				raycast_utils_bonus.c raycasting_bonus.c rendering_bonus.c utils_bonus.c
OBJ_DIR		=	bonus_objects/
OBJS		=	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: libmlx $(BNS_NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)%.o: %.c $(BNS_INC)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(BNS_HDRS) && printf "[Compiling: $(notdir $<)]\n"

$(BNS_NAME): $(OBJS)
	@make -C ../libraries/libft/
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(BNS_HDRS) $(LDFLAGS) -o $(BNS_NAME)
	@printf "[Compiled seccessfully. run ./$(BNS_NAME) <map path>]\n"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(BNS_NAME)

re: clean all

.PHONY: all clean fclean re libmlx