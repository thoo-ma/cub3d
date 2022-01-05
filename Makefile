#############	COMPILER		#############

CC			=	gcc -std=gnu11

FLAGS		=	-Wall -Wextra -Werror

############	DIRECTORIES		#############

SRC_DIR		=	src

LIBFT_DIR	= 	libft

#############	SOURCE FILES	#############

SRCS		=	gnl/gnl.c \
				parse/parse.c \
				parse/get_map.c \
				parse/check_map.c \
				parse/check_space.c \
				parse/get_game_data.c \
				utils/init_cub3d.c \
				utils/exit_cub3d.c \
				utils/array.c \
				utils/mlx.c \
				utils/pixels.c \
				engine/raycasting.c \
				engine/hooks.c \
				engine/move.c \
				engine/rotate.c \
				engine/gfx.c \
				main.c

SOURCES		=	$(addprefix $(SRC_DIR)/,$(SRCS))

#############	OBJECT FILES	#############

OBJS		=	$(addsuffix .o, $(basename $(SRCS)))

OBJECTS		=	$(addprefix $(SRC_DIR)/,$(OBJS))

#############	HEADER FILES	#############

HEADERS		=	include/gnl.h \
				include/cub3d.h

#############	INCLUDES		#############

INCLUDE		=	-I include \
				-I minilibx-linux \
				-I $(LIBFT_DIR)

#############	LIBRARY			#############

LIBFT		= 	$(LIBFT_DIR)/libft.a

############	BINARY			#############

NAME		=	cub3d

############	TARGETS			#############

all:			$(NAME)

$(NAME):		$(LIBFT) $(HEADERS) $(OBJECTS)
				$(CC) $(FLAGS) $(INCLUDE) -o $(NAME) $(OBJECTS) $(LIBFT) \
				-Lminilibx-linux -lmlx -lXext -lX11 -lm

$(OBJECTS):		$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
				$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
				$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
				$(MAKE) --no-print-directory clean -C $(LIBFT_DIR)
				rm -f $(OBJECTS)

fclean:			clean
				$(MAKE) --no-print-directory fclean -C $(LIBFT_DIR)
				rm -f $(NAME)

norminette:
				@norminette include src libft

re:				fclean all

############	PHONY			#############

.PHONY:			all re clean fclean norminette
