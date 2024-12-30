# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/14 13:48:42 by adbouras          #+#    #+#              #
#    Updated: 2024/12/30 18:29:35 by adbouras         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN		= \033[1;92m
YELLOW		= \033[0;93m
RED			= \033[1;91m
RESET		= \033[0;39m

NAME		= cub3d

BNS_NAME	= cub3d_bonus

CC			= cc

CFLAGS		= -Wextra -Wall -Werror  -Wunreachable-code -Ofast

LIBMLX		= ./libraries/MLX42

LIBFT		= ./libraries/libft/libft.a

HEADERS		= -I ./include -I $(LIBMLX)/include

INCLUDES	= ./includes/cub3d.h

LIBS		= $(LIBMLX)/build/libmlx42.a -ldl -L/Users/adhambouras/.brew/lib -lglfw -pthread -lm

SRCS		= main.c get_next_line.c get_next_line_utils.c player_movment.c map_loading.c init.c

BNS_SRCS	= 

OBJ_DIR		= objects/

OBJS		= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

#BOBJECT		= $(BNS_SRCS:.c=.o)

all: libmlx $(NAME)

bonus: libmlx $(BNS_NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)%.o: %.c $(INCLUDES)
	mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@echo "\n$(YELLOW)[Compiling Libft]$(RESET)"
	@make -C ./libraries/libft
	@echo "$(GREEN)[Libft Compiled]$(RESET)"
	@echo "$(GREEN)[ft_print Compiled]$(RESET)"
	@echo "$(YELLOW)[Compiling cub3d]$(RESET)"
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo "$(GREEN)[cub3d Compiled]$(RESET)"

$(BNS_NAME): $(BOBJECT)
	@echo "\n$(YELLOW)[Compiling Libft]$(RESET)"
	@make -C ./libraries/libft
	@echo "$(GREEN)[Libft Compiled]$(RESET)"
	@echo "$(GREEN)[ft_print Compiled]$(RESET)"
	@echo "$(YELLOW)[Compiling Bonus]$(RESET)"
	@$(CC) $(BOBJECT) $(LIBS) $(HEADERS) $(LIBFT) $(PRINTF) -o $(BNS_NAME)
	@echo "$(YELLOW)[Bonus Compiled]$(RESET)"

clean:
	@make clean -C ./libraries/libft
#	@rm -rf $(OBJS) $(BOBJECT)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@echo "$(RED)[Objects Cleaned]$(RESET)"

fclean: clean
	@make fclean -C ./libraries/libft
	@rm -rf $(NAME) $(BNS_NAME)
	@echo "$(RED)[EXEs Cleaned]$(RESET)"

re: fclean all

.PHONY: all, clean, fclean, re, libmlx
