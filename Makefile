CC		=	gcc

FLAGS		=	-Wall -Wextra -Wdouble-promotion -Wfloat-conversion #-fsanitize=address

LIBFT_DIR	= 	src/libft/

LIBFT		= 	$(LIBFT_DIR)libft.a

SRCS		=	src/utils/is_wall.c \
			src/utils/print_data.c \
			src/utils/skip_spaces.c \
			src/utils/skip_digits.c \
			src/utils/arrondi.c \
			src/utils/rotate.c \
			src/parse/parse.c \
			src/parse/get_map.c \
			src/parse/get_game_data.c \
			src/parse/square_map.c \
			src/parse/check_map.c \
			src/gnl/gnl.c \
			src/gfx/pixel_to_image.c \
			src/gfx/square_pixel_to_image.c \
			src/gfx/map_to_image.c \
			src/gfx/rays_to_image.c \
			src/events/key_hook.c \
			src/events/define_hooks.c \
			src/events/do_nothing.c \
			src/raycasting/new_raycasting.c \
			src/utils/init_cub3d.c \
			src/utils/exit_cub3d.c \
			src/utils/array.c \
			src/main.c

INCLUDE		=	-I minilibx-linux \
			-I src/libft \
			-I include

NAME		=	cub3d

%.o:			%.c
			$(CC) $(FLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(LIBFT) $(SRCS)
			@echo Compilng cub3d...
			@$(CC) $(FLAGS) $(INCLUDE) -o $(NAME) $(SRCS) $(LIBFT) -Lminilibx-linux -lmlx -lXext -lX11 -lm

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

re:			fclean all
