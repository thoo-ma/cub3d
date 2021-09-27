/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:19:02 by trobin            #+#    #+#             */
/*   Updated: 2021/09/24 18:36:18 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>		/* open, read */
# include <stdio.h>		/* printf, perror */
# include <unistd.h>	/* close */
# include <stdlib.h>	/* malloc */
# include <string.h>	/* strerror */
# include <math.h>		/* cos, sin, PI */
# include <errno.h>		/* errno */

# include "X11/X.h"
# include "mlx.h"
# include "gnl.h"
# include "libft.h"

/******************************************************************************/
/*						                              */
/*			keycodes                                              */
/*						                              */
/******************************************************************************/

# define W 119
# define A 97
# define S 115
# define D 100
# define Z 122 // remove
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363

/******************************************************************************/
/*						                              */
/*			colors                                                */
/*						                              */
/******************************************************************************/

# define RED			0x00FF0000
# define BLUE			0x000000FF
# define GREEN			0x0000FF00
# define WHITE			0x00F0F0F0
# define BLACK			0x000F0F0F

# define N_COLOR		RED
# define S_COLOR		BLUE
# define E_COLOR		GREEN
# define W_COLOR		WHITE
# define SKY_COLOR		BLACK
# define FLOOR_COLOR	BLACK

/******************************************************************************/
/*						                              */
/*			other                                                 */
/*						                              */
/******************************************************************************/

# define WIN_X 512
# define WIN_Y 512

# define FOV_DEG 60.0
# define FOV_RAD FOV_DEG * M_PI / 180.0

# define SQUARE_LENGTH 1 // 16

# define CARDINALS		"NSEW"
# define BASE_DEC		"0123456789"

# define CUB_LENGTH		1.0 // will be obsolete

// bug if above SQUARE_LENGTH
// to avoid this, check for walls at every next square,
// not only for the square at MOVEMENT_UNIT distance from player
# define MOVEMENT_UNIT	8 // i.e SQUARE_LENGTH / 2

//# define SQUARE_UNIT		1 / SQUARE_LENGTH
//# define MOVEMENT_UNIT	1 * SQUARE_UNIT
//# define PLAYER_HEIGHT	SQUARE_LENGTH / 2

# define ROTATION_UNIT	(M_PI / 2)

# ifndef M_PI
	#define M_PI		3.14159265358979323846
# endif

typedef int		t_bool; // remove

/******************************************************************************/
/*						                              */
/*			errors / exit values                                  */
/*						                              */
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
	MAP_LINE_FORMAT,
	MAP_EXTENSION,
	MAP_NOT_CLOSE,
	MAP_FT_STRNCAT,
	MAP_FT_SPLIT,
	MAP_DUPLICATE,
	MAP_UNDEFINED,
	MAP_NO_CARDINAL,
	MAP_MULT_CARDINALS,
	MLX_INIT,
	MLX_WINDOW,
	XPM_FORMAT,
	XPM_DUPLICATE,
	XPM_UNAVAILABLE,
	TEXTURE_MISSING,
	IMG_ADDR,
	COLOR_FORMAT,
	COLOR_MALLOC,
	COLOR_RANGE,
	COLOR_MISSING,
	COLOR_DUPLICATE,
	MAIN_ARG,
	ERRORS
}	t_errno;

/******************************************************************************/
/*						                              */
/*			2D vectors                                            */
/*						                              */
/******************************************************************************/

typedef struct	s_int_vector
{
	int	x;
	int	y;
}				t_int_vector;

typedef struct	s_uint_vector
{
	unsigned int x;
	unsigned int y;
}				t_uint_vector;

typedef	struct	s_double_vector
{
	double x;
	double y;
}				t_double_vector;

/******************************************************************************/
/*						                              */
/*			pixel representation                                  */
/*						                              */
/******************************************************************************/

typedef struct	s_color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char parsed;
}				t_color;

/******************************************************************************/
/*						                              */
/*			all pixel colors cub3d uses                           */
/*						                              */
/******************************************************************************/

typedef struct	s_colors
{
	t_color floor;
	t_color ceiling;
}				t_colors;

/******************************************************************************/
/*                                                                            */
/*		all mlx image's useful data in one place                      */
/*                                                                            */
/******************************************************************************/

typedef	struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}				t_img;

/******************************************************************************/
/*                                                                            */
/*		all mlx images cub3d uses                                     */
/*                                                                            */
/******************************************************************************/

typedef struct s_images
{
	t_img	est;
	t_img	west;
	t_img	north;
	t_img	south;
}				t_images;

/******************************************************************************/
/*						                              */
/*			player                                                */
/*						                              */
/******************************************************************************/

typedef struct	s_player
{
	double				dir;
	double				plane;
	t_int_vector		map;
	t_double_vector		pos;
}				t_player;

/******************************************************************************/
/*						                              */
/*			data                                                  */
/*						                              */
/******************************************************************************/

typedef	struct	s_data
{
	void		*mlx_ptr;
	void		*win;
	char		**map;
	const char	*my_strerror[ERRORS + 1];
	t_images	images;
	t_colors	colors;
	t_player	player;
}				t_data;

/******************************************************************************/
/*                                                                            */
/*		parse/                                                        */
/*                                                                            */
/******************************************************************************/

/*			parse.c				*/
int			open_map(t_data *data, char *filename);
void			check_file_extension(t_data *data, char *filename);
void			check_game_data(t_data *data);
void			parse(t_data *data, char *filename);

/*			get_map.c			*/
void			safe_free(void **a);
void			try_ft_strncat(t_data *data, char **dst, char *src, int n);
void			get_map(t_data *data, int fd, char **line);

/*			get_game_data			*/
void			get_texture(t_data *data, t_img *img, char *line);
void			get_color(t_data *data, t_color *color, char *line);
void			check_color_digits(t_data *data, char **tmp, int i);
void			check_color_range(t_data *data, char **tmp, int i);
void			get_game_data(t_data *data, char *line);

/*			check_map.c			*/
char			*get_left_cell(char **map, int row, int col);
char			*get_right_cell(char **map, int row, int col);
char			*get_upper_cell(char **map, int row, int col);
char			*get_lower_cell(char **map, int row, int col);
int			elems_index(char *s1, char *s2);
void			get_player_data(t_player *player, int x, int y, char c);
void			check_undefined_cells(t_data *data);
void			check_cardinal(t_data *data, char **map);
void			check_space(t_data *data, char **map, int row, int col);
void			check_map_closed(t_data *data, char **map);
void			check_map(t_data *data);

/*			square_map.c			*/
int			get_max_len(char **map);
t_bool			square_map(char **map);

/******************************************************************************/
/*                                                                            */
/*		utils/                                                        */
/*                                                                            */
/******************************************************************************/

/*			print_data.c			*/
void			print_player_data(t_player *player);
void			print_image_data(t_img *img, const char *s);
void			print_color_data(t_color *color, const char *s);
void			print_data(t_data *data);

void			skip_spaces(char **s);
void			skip_digits(char **s);
int			is_wall(char **map, int x, int y);
double			arrondi(double z);
double			rotate(double ray, double angle);

/*			array.c				*/
int			length_2d_array(char **a);
void			free_2d_array(char **a);
void			print_2d_array(char **a);

/*			init_cub3d.c			*/
void			get_mlx_instance(t_data *data);
void			get_mlx_window(t_data *data);
void			init_cub3d(t_data *data);
void			init_colors(t_colors *colors);
void			init_images(t_images *images);
void			init_my_strerror(const char **my_strerror);

/*			exit_cub3d.c			*/
void			destroy_cub3d(t_data *data);
void			exit_cub3d(t_data *data, int my_errno);

/******************************************************************************/
/*                                                                            */
/*		gfx/                                                          */
/*                                                                            */
/******************************************************************************/

int			map_to_image(t_img *img, char **map);
void			rays_to_image(t_img *img, double *posx, double *posy,
				double *dirx, double *diry, char **map);
void			erase_rays_from_image(t_img *img, double *posx, double *posy,
				double *dirx, double *diry, char **map);
void			pixel_to_image(t_img *img, int y, int x, int color);
void			square_pixel_to_image(t_img *img, int y, int x, int color);
void			ray_EW_to_image(double rayx, double intersecx, double intersecy,
				double deltay, t_img *img);
void			ray_NS_to_image(double rayy, double intersecx, double intersecy,
				double deltax, t_img *img);

/******************************************************************************/
/*                                                                            */
/*		events/                                                       */
/*                                                                            */
/******************************************************************************/

int			do_nothing(void *param);
int			key_hook(int key, t_data *data);
void			define_hooks(t_data *data);

/******************************************************************************/
/*                                                                            */
/*		raycasting/                                                   */
/*                                                                            */
/******************************************************************************/

void			raycasting(t_data *data);
void			cast(t_double_vector pos, double ray, t_img *img,
				t_double_vector *resolution, int column, t_data *data);
int			is_wall_EW(double intersecx, double intersecy,
				double rayx, char **map);
int			is_wall_NS(double intersecx, double intersecy,
				double rayy, char **map);
double			get_dist_EW(double posx, double posy,
				double rayx, double rayy,
				char **map, double angle, t_img *img);
double			get_dist_NS(double posx, double posy,
				double rayx, double rayy,
				char **map, double angle, t_img *img);
void			column_to_image(unsigned int color, double dist, t_img *img,
				t_double_vector resolution, int column);

#endif
