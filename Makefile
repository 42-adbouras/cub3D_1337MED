NAME		= cub3D
CFLAGS		= -Wextra -Wall -Werror #-fsanitize=address -g
#LDFLAGS		= -fsanitize=address -g
LIBMLX		= ./libraries/MLX42
LIBFT		= ./libraries/libft/libft.a

HEADERS		= -I ./include -I $(LIBMLX)/include
LIBS		= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		= main.c get_next_line.c get_next_line_utils.c init.c map_loading.c player_movment.c raycasting.c utils.c clean_up.c game_loop.c rendering.c
OBJ_DIR		= objects/
OBJS		= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@make -C ./libraries/libft/
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) $(LDFLAGS) -o $(NAME)

clean:
	@make clean -C ./libraries/libft/
	rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@make fclean -C ./libraries/libft/
	@rm -rf $(NAME)

re: clean all

.PHONY: all clean fclean re libmlx