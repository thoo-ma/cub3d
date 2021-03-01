OBJS	=	src/libft/elem_index.o \
			src/libft/ft_isdigit.o \
			src/libft/ft_atoi.o \
			src/libft/ft_bzero.o \
			src/libft/ft_split.o \
			src/libft/ft_memchr.o \
			src/libft/ft_memcpy.o \
			src/libft/ft_memset.o \
			src/libft/ft_strlen.o \
			src/libft/ft_strcmp.o \
			src/libft/ft_strchr.o \
			src/libft/ft_strcpy.o \
			src/libft/ft_strdup.o \
			src/libft/ft_strndup.o \
			src/libft/ft_strcspn.o \
			src/libft/ft_strpbrk.o \
			src/libft/ft_strptrlen.o \
			src/utils/is_wall.o \
			src/utils/print_data.o \
			src/utils/skip_spaces.o \
			src/utils/skip_digits.o \
			src/utils/arrondi.o \
			src/utils/rotate.o \
			src/parse/parse.o \
			src/parse/get_map.o \
			src/parse/get_game_data.o \
			src/parse/square_map.o \
			src/parse/check_map.o \
			src/gnl/gnl.o \
			src/gfx/pixel_to_image.o \
			src/gfx/square_pixel_to_image.o \
			src/gfx/map_to_image.o \
			src/gfx/rays_to_image.o \
			src/events/key_hook.o \
			src/events/define_hooks.o \
			src/events/do_nothing.o \
			src/raycasting/new_raycasting.o \
			src/utils/init_cub3d.o \
			src/utils/exit_cub3d.o \
			src/utils/array.o

CC		=	gcc

FLAGS	=	-Wall -Wextra -Wdouble-promotion -Wfloat-conversion #-fsanitize=address

#INCLUDE	=	-I minilibx-linux/mlx.h

%.o:		%.c
			$(CC) $(FLAGS) -c $< -o $@

#all:		$(OBJS)
#			$(CC) $(FLAGS) $(OBJS) main.c

all:		$(OBJS)
			$(CC) $(FLAGS) $(INCLUDE) -o main.o -c main.c
			$(CC) $(FLAGS) $(INCLUDE) -o a.out $(OBJS) main.o -Lminilibx-linux -lmlx -lXext -lX11 -lm

clean:
			rm -rf $(OBJS) main.o

fclean:		clean
			rm -rf a.out

re:			fclean all
