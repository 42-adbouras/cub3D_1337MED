# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 11:59:01 by adbouras          #+#    #+#              #
#    Updated: 2025/02/26 19:13:26 by adbouras         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRN	= \033[1;92m
YLW	= \033[1;93m
RED	= \033[1;91m
RST	= \033[0;39m

CC			=	cc
NAME		=	cub3D
BNS_NAME	=	cub3D_bonus
CFLAGS		=	-Wextra -Wall -Werror -O3 #-fsanitize=address -g
LDFLAGS		=	-fsanitize=address -g
LIBMLX		=	libraries/MLX42
LIBFT		=	libraries/libft/libft.a

HEADERS		=	-I ./include -I $(LIBMLX)/include
INCLUDES	=	includes/cub3d.h includes/get_next_line.h
LIBS		=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		=	clean_up.c game_loop.c get_next_line.c get_next_line_utils.c init.c main.c map_loading.c parsing/main_parse.c \
				player_movment.c raycasting.c textures/rendering.c utils.c raycast_utils.c parsing/parse_colors.c parsing/parse_elements.c \
				parsing/check_map.c parsing/parse_utils.c parsing/parse_more_utils.c textures/texture_utils.c parsing/extract_map_content.c
BNS_SRCS	=	bonus/clean_up_bonus.c \
				bonus/game_loop_bonus.c \
				bonus/get_next_line_bonus.c \
				bonus/get_next_line_utils_bonus.c \
				bonus/init_bonus.c \
				bonus/main_bonus.c \
				bonus/parsing_bonus/check_map_bonus.c \
				bonus/parsing_bonus/extract_map_content_bonus.c \
				bonus/parsing_bonus/main_parse_bonus.c \
				bonus/parsing_bonus/parse_colors_bonus.c \
				bonus/parsing_bonus/parse_elements_bonus.c \
				bonus/parsing_bonus/parse_more_utils_bonus.c \
				bonus/parsing_bonus/parse_utils_bonus.c \
				bonus/player_movment_bonus.c \
				bonus/raycast_utils_bonus.c \
				bonus/raycasting_bonus.c \
				bonus/textures_bonus/rendering_bonus.c \
				bonus/textures_bonus/texture_utils_bonus.c \
				bonus/utils_bonus.c \
				bonus/map_loading_bonus.c 
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
