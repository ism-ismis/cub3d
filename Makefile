NAME = cub3D
SRCS =	main.c \
		./read_cub/arrange_map.c \
		./read_cub/check_map.c \
		./read_cub/check_map2.c \
		./read_cub/get_next_line.c \
		./read_cub/get_next_line_utils.c \
		./read_cub/read_cub.c \
		./read_cub/read_cub_utils.c \
		./read_cub/texture_color.c \
		./game_engine/bitmap.c \
		./game_engine/game_manage.c \
		./game_engine/get_textures.c \
		./game_engine/init_free.c \
		./game_engine/init_info.c \
		./game_engine/player_move.c \
		./game_engine/player_move2.c \
		./draw/draw.c \
		./draw/draw_wall.c \
		./draw/draw_sprites.c \
		./draw/draw_sprites2.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft
LIBFT_LIB = ./libft/libft.a

MLX_DIR = ./minilibx-linux
MLX_LIB = ./minilibx-linux/libmlx_Linux.a
MLX_LIB_CUR = libmlx_Linux.a
CLIB = -lXext -lX11
CFLAGS = -Wall -Wextra -Werror

CC = gcc -g -I $(MLX_DIR)

RM = rm -f

all:	$(NAME)

$(NAME): $(OBJS)
		$(MAKE) -C $(LIBFT_DIR)
		$(MAKE) bonus -C $(LIBFT_DIR)
		$(MAKE) -C $(MLX_DIR)
		cp $(MLX_LIB) ./
		$(CC) $(CFLAGS) $(OBJS) -L. -L.minilibx-linux -lmlx_Linux $(CLIB) -lm $(LIBFT_LIB) -o $(NAME)

clean:
		$(RM) $(OBJS)
		$(MAKE) clean -C $(MLX_DIR)
		$(MAKE) clean -C $(LIBFT_DIR)

fclean:	clean
		$(RM) $(NAME)
		$(RM) $(MLX_LIB_CUR)
		$(MAKE) clean -C $(MLX_DIR)
		$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
