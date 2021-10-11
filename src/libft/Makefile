NAME	=	libft.a

SRCS	=	ft_atoi.c	\
			ft_split.c	\
			ft_bzero.c	\
			ft_memcpy.c	\
			ft_memchr.c	\
			ft_memset.c	\
			ft_strchr.c	\
			ft_strlen.c	\
			ft_strcmp.c	\
			ft_strcpy.c	\
			ft_strdup.c	\
			ft_strndup.c	\
			ft_strcspn.c	\
			ft_strpbrk.c	\
			ft_isdigit.c	\
			elem_index.c	\
			elems_index.c	\
			ft_strptrlen.c

OBJS	=	$(addsuffix .o, $(basename $(SRCS)))

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror

ARCHIVE	=	ar -rcs $(NAME)

all:		$(NAME)

%.o:		%.c
			@$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			@$(ARCHIVE) $^

clean:
			@rm -f $(OBJS)

fclean:			clean
			@rm -f $(NAME)

re:			fclean all
