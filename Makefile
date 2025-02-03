# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 11:59:01 by adbouras          #+#    #+#              #
#    Updated: 2025/02/03 14:29:36 by adbouras         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRN	= \033[1;92m
YLW	= \033[1;93m
RED	= \033[1;91m
RST	= \033[0;39m

CC			=	cc
NAME		=	cub3D
BNS_NAME	=	cub3D_bonus
CFLAGS		=	-Wextra -Wall -Werror -fsanitize=address -g
LDFLAGS		=	-fsanitize=address -g
LIBMLX		=	libraries/MLX42
LIBFT		=	libraries/libft/libft.a

HEADERS		=	-I ./include -I $(LIBMLX)/include
INCLUDES	=	includes/cub3d.h includes/get_next_line.h
LIBS		=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		=	clean_up.c game_loop.c get_next_line.c get_next_line_utils.c init.c main.c map_loading.c parse_map.c \
				player_movment.c raycasting.c rendering.c utils.c raycast_utils.c
OBJ_DIR		=	objects/
OBJS		=	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: libmlx $(NAME)

bonus:
	@make -C bonus/
	@mv bonus/$(BNS_NAME) .
libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)%.o: %.c $(INCLUDES)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "$(YLW)[Compiling: $(notdir $<)]\n$(RST)"

$(NAME): $(OBJS)
	@make -C ./libraries/libft/
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) $(LDFLAGS) -o $(NAME)
	@printf "[Compiled seccessfully. run ./$(NAME) <map path>]\n"

clean:
	@make clean -C libraries/libft/
	@make clean -C bonus/
	@rm -rf $(OBJ_DIR) && echo
	@rm -rf $(LIBMLX)/build

fclean: clean
	@make fclean -C libraries/libft/
	@make fclean -C bonus/
	@rm -rf $(NAME) $(BNS_NAME)

re: clean all

.PHONY: all clean fclean re libmlx bonus