# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 11:59:01 by adbouras          #+#    #+#              #
#    Updated: 2025/03/16 15:38:18 by adbouras         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRN			=	\033[1;92m
YLW			=	\033[1;93m
RED			=	\033[1;91m
RST			=	\033[0;39m

CC			=	cc
NAME		=	cub3D
BNS_NAME	=	cub3D_bonus
CFLAGS		=	-Wextra -Wall -Werror -O3
# LDFLAGS		=	-fsanitize=address -g
LIBMLX		=	/Users/$(USER)/MLX42
LIBFT		=	libraries/libft/libft.a

HEADERS		=	-I ./includes -I $(LIBMLX)/include
LIBS		=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

MAN_SRC_DIR	=	mandatory
BNS_SRC_DIR	=	bonus

SRCS		=	$(shell find $(MAN_SRC_DIR) -name '*.c') 
BNS_SRCS	=	$(shell find $(BNS_SRC_DIR) -name '*.c')
OBJ_DIR		=	objects/
OBJS		=	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
BNS_OBJS	=	$(addprefix $(OBJ_DIR), $(BNS_SRCS:.c=.o))

all: libmlx $(NAME)

bonus: libmlx $(BNS_NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "$(YLW)[Compiling: $(notdir $<)]\n$(RST)"

$(NAME): $(OBJS)
	@make -C ./libraries/libft/
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) $(LDFLAGS) -o $(NAME)
	@printf "$(GRN)[Compiled seccessfully. run ./$(NAME) <map path>]\n$(RST)"

$(BNS_NAME): $(BNS_OBJS)
	@make -C ./libraries/libft/
	@$(CC) $(BNS_OBJS) $(LIBS) $(LIBFT) $(HEADERS) $(LDFLAGS) -o $(BNS_NAME)
	@printf "$(GRN)[Compiled seccessfully. run ./$(BNS_NAME) <map path>]\n$(RST)"

clean:
	@make clean -C libraries/libft/
	@rm -rf $(OBJ_DIR) && printf "$(RED)[Objects cleaned]\n$(RST)"
	@rm -rf $(LIBMLX)/build

fclean: clean
	@make fclean -C libraries/libft/
	@rm -rf $(NAME) $(BNS_NAME) && printf "$(RED)[Removed executables]$(RST)\n"

re: fclean all

.PHONY: all clean fclean re libmlx bonus
