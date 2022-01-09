/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:19:02 by trobin            #+#    #+#             */
/*   Updated: 2022/01/03 19:13:11 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include "mlx.h"
# include "gnl.h"
# include "libft.h"
# include "X11/X.h"

/******************************************************************************/
/*						                                                      */
/*		keycodes                                                              */
/*						                                                      */
/******************************************************************************/

# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363

/******************************************************************************/
/*						                                                      */
/*		config                                                                */
/*						                                                      */
/******************************************************************************/

# define CUB_SIZE 64
# define WIN_SIZE 1024
# define FOV 66.0
# define ROTATION_UNIT 10
# define MOVEMENT_UNIT 20
# define BASE_DEC "0123456789"

/******************************************************************************/
/*						                                                      */
/*		errors / exit values                                                  */
/*						                                                      */
/******************************************************************************/

typedef enum e_errno
{
	ZERO,
	MAP_MALLOC,
	MAP_ENOENT,
	MAP_EACCES,
	MAP_EISDIR,
	MAP_OPEN,
	MAP_READ,
	MAP_FT_SPLIT,
	MAP_FT_STRNCAT,
	MAP_EXTENSION,
	MAP_NOT_CLOSE,
	MAP_DUPLICATE,
	MAP_UNDEFINED,
	MAP_LINE_FORMAT,
	MAP_NO_CARDINAL,
	MAP_MULT_CARDINALS,
	IMG_ADDR,
	MLX_INIT,
	MLX_WINDOW,
	MLX_NEW_IMAGE,
	XPM_SIZE,
	XPM_FORMAT,
	XPM_DUPLICATE,
	XPM_UNAVAILABLE,
	XPM_MISSING,
	COLOR_FORMAT,
	COLOR_MALLOC,
	COLOR_RANGE,
	COLOR_MISSING,
	COLOR_DUPLICATE,
	MAIN_ARG,
	ERRORS
}	t_errno;

/******************************************************************************/
/*						                                                      */
/*		2D vectors                                                            */
/*						                                                      */
/******************************************************************************/

typedef struct s_int_vector
{
	int	x;
	int	y;
}		t_int_vector;

typedef struct s_double_vector
{
	double	x;
	double	y;
}			t_double_vector;

/******************************************************************************/
/*						                                                      */
/*		pixel representation                                                  */
/*						                                                      */
/******************************************************************************/

typedef struct s_color
{
	int				color;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	parsed;
}					t_color;

/******************************************************************************/
/*						                                                      */
/*		all pixel colors cub3d uses                                           */
/*						                                                      */
/******************************************************************************/

typedef struct s_colors
{
	t_color	floor;
	t_color	ceiling;
}			t_colors;

/******************************************************************************/
/*                                                                            */
/*		all mlx image's useful data in one place                              */
/*                                                                            */
/******************************************************************************/

typedef struct s_image
{
	void	*img;
	int		*addr;
	int		bpp;
	int		ll;
	int		endian;
}			t_image;

/******************************************************************************/
/*                                                                            */
/*		all mlx images cub3d uses                                             */
/*                                                                            */
/******************************************************************************/

typedef struct s_images
{
	t_image	est;
	t_image	west;
	t_image	north;
	t_image	south;
	t_image	cub3d;
}			t_images;

/******************************************************************************/
/*						                                                      */
/*		player                                                                */
/*						                                                      */
/******************************************************************************/

typedef struct s_player
{
	double			fov;
	double			rot;
	double			mov;
	double			dir;
	t_int_vector	map;
	t_double_vector	pos;
}					t_player;

/******************************************************************************/
/*						                                                      */
/*		ray                                                                   */
/*						                                                      */
/******************************************************************************/

typedef struct s_ray
{
	int				column;
	double			rot;
	double			angle;
	t_int_vector	map;
	t_int_vector	step;
	t_double_vector	dist;
	t_double_vector	delta;
}					t_ray;

/******************************************************************************/
/*						                                                      */
/*		wall                                                                  */
/*						                                                      */
/******************************************************************************/

typedef struct s_wall
{
	int				lo;
	int				hi;
	int				height;
	int				column;
	double			dist;
	t_image			*texture;
}			t_wall;

/******************************************************************************/
/*						                                                      */
/*		data                                                                  */
/*						                                                      */
/******************************************************************************/

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	t_ray		ray;
	t_wall		wall;
	t_player	player;
	t_colors	colors;
	t_images	images;
	const char	*my_strerror[ERRORS + 1];
}				t_data;

/******************************************************************************/
/*                                                                            */
/*             parse/                                                         */
/*                                                                            */
/******************************************************************************/

/*				parse.c					*/
void			parse(t_data *data, char *filename);

/*				get_map.c				*/
void			safe_free(void **a);
void			try_ft_strncat(t_data *data, char **dst, char *src, int n);
void			get_map(t_data *data, int fd, char **line);

/*				get_game_data			*/
void			get_game_data(t_data *data, char *line);

/*				check_map.c				*/
void			get_player_data(t_player *player, int x, int y, char c);
void			check_space(t_data *data, char **map, int row, int col);
void			check_map(t_data *data);

/******************************************************************************/
/*                                                                            */
/*              utils/                                                        */
/*                                                                            */
/******************************************************************************/

/*				mlx_utils.c				*/
void			get_mlx_image(t_data *data);
void			get_mlx_window(t_data *data);
void			get_mlx_instance(t_data *data);

/*				array.c					*/
int				length_2d_array(char **a);
void			free_2d_array(char **a);
void			print_2d_array(char **a);
void			skip_spaces(char **s);
void			skip_digits(char **s);

/*				init_cub3d.c			*/
void			get_mlx_window(t_data *data);
void			init_cub3d(t_data *data);

/*				exit_cub3d.c			*/
void			exit_cub3d(t_data *data, int my_errno);

/******************************************************************************/
/*                                                                            */
/*              rotate.c                                                      */
/*                                                                            */
/******************************************************************************/

double			rotate(double ray, double angle);
void			rotate_player(t_player *player, double angle);

/******************************************************************************/
/*                                                                            */
/*              gfx.c                                                         */
/*                                                                            */
/******************************************************************************/

void			textured_column_to_image(t_data *data);

/******************************************************************************/
/*                                                                            */
/*              pixels.c                                                      */
/*                                                                            */
/******************************************************************************/

void			pixel_to_image(t_image *image, int x, int t, int color);
int				get_image_pixel_color(t_image *image, int x, int y);

/******************************************************************************/
/*                                                                            */
/*              move.c                                                        */
/*                                                                            */
/******************************************************************************/

void			move(t_data *data, double dir);

/******************************************************************************/
/*                                                                            */
/*              hooks.c                                                       */
/*                                                                            */
/******************************************************************************/

void			define_hooks(t_data *data);

/******************************************************************************/
/*                                                                            */
/*              raycasting.c                                                  */
/*                                                                            */
/******************************************************************************/

void			dda(t_data *data);
void			raycasting(t_data *data);
t_int_vector	get_step(double ray);

#endif
