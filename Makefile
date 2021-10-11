CC			=	gcc -std=gnu11

FLAGS		=	-Wall -Wextra -Werror

LIBFT_DIR	= 	src/libft/

LIBFT		= 	$(LIBFT_DIR)libft.a

SRCS		=	src/gnl/gnl.c \
				src/parse/parse.c \
				src/parse/get_map.c \
				src/parse/check_map.c \
				src/parse/check_space.c \
				src/parse/get_game_data.c \
				src/utils/init_cub3d.c \
				src/utils/exit_cub3d.c \
				src/utils/array.c \
				src//utils/mlx.c \
				src/raycasting.c \
				src/hooks.c \
				src/move.c \
				src/rotate.c \
				src/pixels.c \
				src/gfx.c \
				src/main.c

INCLUDE		=	-I minilibx-linux \
				-I src/libft \
				-I src/gnl \
				-I include

NAME		=	cub3d

%.o:			%.c
				$(CC) $(FLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(LIBFT) $(SRCS)
				@echo Compiling cub3d...
				@$(CC) $(FLAGS) $(INCLUDE) -o $(NAME) $(SRCS) $(LIBFT) \
				-Lminilibx-linux -lmlx -lXext -lX11 -lm

$(LIBFT):
				@echo Building libft...
				@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
				@echo Cleaning objects...
				@$(MAKE) --no-print-directory clean -C $(LIBFT_DIR)

fclean:
				@echo Cleaning binaries...
				@$(MAKE) --no-print-directory fclean -C $(LIBFT_DIR)
				@rm -f $(NAME)

norminette:
				@norminette include src

re:				fclean all
