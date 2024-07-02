/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:54:07 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/07 15:54:09 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./Libft/libft/libft.h"
# include "./Libft/gnl/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "./mlx/mlx.h"

# define AERR "Invalid argument\n"
# define MERR "Memory allocation failed\n"
# define FERR "Filename extension error\n"
# define MAPERR "Map Error\n"
# define CPPPMAX 600
# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define WIN_W 2560
# define WIN_H 1440
# define WIN_EDGE_W 320
# define WIN_EDGE_H 80
# define SCALE 35
# define ZSCALE 0.125
# define HEX_LEN 16
# define COLOR_LEN 8
# define TRAN 50
# define RATIO_P 1.2
# define RATIO_M 0.8
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_ROTATE_X 12
# define KEY_ROTATE_Y 13
# define KEY_ROTATE_Z 14
# define KEY_BONUS 11

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_vector
{
	double	c[4];
}	t_vector;

typedef struct s_coordinate
{
	int	x;
	int	y;
}	t_co;

typedef struct s_vertex
{
	t_vector	*vec;
	int			r;
	int			g;
	int			b;
	t_co		co;
}	t_vertex;

typedef struct s_lookat_matrix
{
	t_vector	*eye_position;
	t_vector	*eye_direction;
	t_vector	*up_direction;
	double		**matrix;
	double		**r_matrix;
}	t_lookat_matrix;

typedef struct s_map
{
	int				width;
	int				height;
	int				scale;
	int				scale_cnt;
	int				uscale_cnt;
	int				trans;
	int				min_x;
	int				min_y;
	int				max_x;
	int				max_y;
	int				max_z;
	int				start_x;
	int				start_y;
	int				start_x_trans;
	int				start_y_trans;
	double			start_rot_x;
	double			start_rot_y;
	double			start_rot_z;
	int				flag;
	t_vertex		**matrix;
	t_vertex		**back_up;
	t_lookat_matrix	*la_matrix;
}	t_map;

typedef struct s_var
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;
	t_image	image;
}	t_var;

enum e_xyzw
{
	X = 0,
	Y,
	Z,
	W
};

// main.c
void		set_image(t_var *var);

// parse.c
t_map		*init_map(char *map);
void		read_fdf_file(t_map *map, int fd, char ***db);
void		check_width(t_map *map, char **strs);
void		alloc_matrix(t_map *map);
void		parse_matrix(t_map *map, char ***db);

// parse_utils.c
void		parse_color(t_vertex *vertex, char *str);
void		parse_rgb(t_vertex *vertex, char *str, int len);
int			check_hex(char *str);
void		cut_newline(char **line);
void		free_dmatrix(double **matrix);

// error.c
void		check_input_error(int argc, char *argv);
void		exit_error(char *s);
int			check_fdf(char *str);
void		check_error(int ret, int target);

// utils.c
int			check_str_digit(char *str);
int			check_str_int(char *str);
void		dup_matrix(t_map *map);
void		calculate_scale(t_map *map);
void		calculate_start_trans(t_map *map, int dst_x, int dst_y);

// utils2.c
void		free_db(t_map *map, char ***db);
void		free_strs(char **strs);
void		alloc_lookat_matrix(t_map *map);
double		**alloc_dmatrix(int n);
void		mul_matrix(double **m1, double **m2, double **ret);

// transform_matrix.c
void		transform_matrix(t_map *map);
void		calculate_matrix(t_map *map, double **matrix_ret);
void		calculate_vertex(t_vertex *v, double **matrix);
void		init_lookat_matrix(t_map *map, t_vector *r0, t_vector *r1, \
t_vector *r2);
void		copy_matrix_values(t_map *map, t_vertex ***m1, t_vertex ***m2);

// matrix_utils.c
void		scale_transform(t_map *map, double scale);
void		translate_transform(t_map *map, int x, int y);
void		change_direction(t_map *map);
void		zscale_transform(t_map *map);
void		calculate_max(t_map *map);
void		rotate(t_map *map, double angle);

// draw_image.c
void		draw_image(t_image *img, t_map *map);
void		bre_low_plus(t_vertex cur, t_vertex next, t_image *img);
void		bre_low_minus(t_vertex cur, t_vertex next, t_image *img);
void		bre_high_plus(t_vertex cur, t_vertex next, t_image *img);
void		bre_high_minus(t_vertex cur, t_vertex next, t_image *img);

// bresenham.c
int			create_argb(int a, int r, int g, int b);
void		put_pixel(t_image *img, t_vertex vertex);
void		bresenham(t_vertex cur, t_vertex next, t_image *img);
void		bre_low(t_vertex cur, t_vertex next, t_image *img);
void		bre_high(t_vertex cur, t_vertex next, t_image *img);

// vector.c
t_vector	*set_vector(double x, double y, double z, double w);
t_vector	*normalize_vector1(t_vector *vector);
void		normalize_vector2(t_vector *vector);
t_vector	*cross_vector(t_vector *v1, t_vector *v2);
double		dot_vector(t_vector *v1, t_vector *v2);

// mlxhook.c
void		trans_hook(int keycode, t_var *var);
void		scale_hook(int keycode, t_var *var);
void		rotation_hook(int keycode, t_var *var);
void		rotation_loop(t_map *map, int c);

// rotation.c
void		init_rx_matrix(double **matrix, double angle);
void		init_ry_matrix(double **matrix, double angle);
void		init_rz_matrix(double **matrix, double angle);
void		normalize_matrix_value(t_map *map);
void		init_map_info(t_map *map);

// rotation_utils.c
void		rscale_transform(t_map *map);
void		free_vector(t_vector *r0, t_vector *r1, t_vector *r2);

#endif
