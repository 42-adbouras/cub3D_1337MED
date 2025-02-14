# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: starscourge <starscourge@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 11:59:01 by adbouras          #+#    #+#              #
#    Updated: 2025/02/14 19:10:30 by starscourge      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRN	= \033[1;92m
YLW	= \033[1;93m
RED	= \033[1;91m
RST	= \033[0;39m

CC			=	cc
NAME		=	cub3D
BNS_NAME	=	cub3D_bonus
CFLAGS		=	-Wextra -Wall -Werror #-fsanitize=address -g
# LDFLAGS		=	-fsanitize=address -g
LIBMLX		=	libraries/MLX42
LIBFT		=	libraries/libft/libft.a

HEADERS		=	-I ./include -I $(LIBMLX)/include
INCLUDES	=	includes/cub3d.h includes/get_next_line.h
LIBS		=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		=	clean_up.c game_loop.c get_next_line.c get_next_line_utils.c init.c main.c map_loading.c parsing/parse_map.c \
				player_movment.c raycasting.c rendering.c utils.c raycast_utils.c parsing/parse_colors.c parsing/parse_elements.c \
				parsing/check_map.c parsing/parse_utils.c
BNS_SRCS	=	bonus/clean_up_bonus.c bonus/game_loop_bonus.c bonus/get_next_line_bonus.c  bonus/get_next_line_utils_bonus.c \
				bonus/init_bonus.c bonus/main_bonus.c bonus/map_loading_bonus.c bonus/parse_map_bonus.c bonus/player_movment_bonus.c \
				bonus/raycast_utils_bonus.c bonus/raycasting_bonus.c bonus/rendering_bonus.c bonus/utils_bonus.c
OBJ_DIR		=	objects/
OBJS		=	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
BNS_OBJS	=	$(addprefix $(OBJ_DIR), $(BNS_SRCS:.c=.o))

all: libmlx $(NAME)

bonus: libmlx $(BNS_NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)%.o: %.c $(INCLUDES)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "$(YLW)[Compiling: $(notdir $<)]\n$(RST)"

$(NAME): $(OBJS)
	@make -C ./libraries/libft/
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) $(LDFLAGS) -o $(NAME)
	@printf "[Compiled seccessfully. run ./$(NAME) <map path>]\n"

$(BNS_NAME): $(BNS_OBJS)
	@make -C ./libraries/libft/
	@$(CC) $(BNS_OBJS) $(LIBS) $(LIBFT) $(HEADERS) $(LDFLAGS) -o $(BNS_NAME)
	@printf "[Compiled seccessfully. run ./$(BNS_NAME) <map path>]\n"

clean:
	@make clean -C libraries/libft/
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@make fclean -C libraries/libft/
	@rm -rf $(NAME) $(BNS_NAME)

re: clean all

.PHONY: all clean fclean re libmlx bonus