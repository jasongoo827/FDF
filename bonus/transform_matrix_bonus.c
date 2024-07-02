/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_matrix_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:47:23 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/12 12:47:24 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	transform_matrix(t_map *map)
{
	t_vector	*r0;
	t_vector	*r1;
	t_vector	*r2;
	double		**tmp;

	tmp = alloc_dmatrix(4);
	r2 = normalize_vector1(map->la_matrix->eye_direction);
	r0 = cross_vector(r2, map->la_matrix->up_direction);
	normalize_vector2(r0);
	r1 = cross_vector(r2, r0);
	normalize_vector2(r1);
	init_lookat_matrix(map, r0, r1, r2);
	init_rz_matrix(map->la_matrix->r_matrix, M_PI / 2);
	mul_matrix(map->la_matrix->matrix, map->la_matrix->r_matrix, tmp);
	calculate_matrix(map, tmp);
	change_direction(map);
	calculate_max(map);
	calculate_scale(map);
	scale_transform(map, (double)map->scale);
	calculate_max(map);
	calculate_start_trans(map, map->start_x, map->start_y);
	copy_matrix_values(map, &map->back_up, &map->matrix);
	translate_transform(map, map->start_x_trans, map->start_y_trans);
	free_vector(r0, r1, r2);
	free_dmatrix(tmp);
}

void	init_lookat_matrix(t_map *map, t_vector *r0, t_vector *r1, t_vector *r2)
{
	double		d0;
	double		d1;
	double		d2;
	double		**matrix;

	d0 = dot_vector(map->la_matrix->eye_position, r0);
	d1 = dot_vector(map->la_matrix->eye_position, r1);
	d2 = dot_vector(map->la_matrix->eye_position, r2);
	matrix = map->la_matrix->matrix;
	matrix[0][0] = r0->c[X];
	matrix[1][0] = r0->c[Y];
	matrix[2][0] = r0->c[Z];
	matrix[0][1] = r1->c[X];
	matrix[1][1] = r1->c[Y];
	matrix[2][1] = r1->c[Z];
	matrix[0][2] = r2->c[X];
	matrix[1][2] = r2->c[Y];
	matrix[2][2] = r2->c[Z];
	matrix[0][3] = 0;
	matrix[1][3] = 0;
	matrix[2][3] = 0;
	matrix[3][0] = d0;
	matrix[3][1] = d1;
	matrix[3][2] = d2;
	matrix[3][3] = 1;
}

void	calculate_matrix(t_map *map, double **matrix_ret)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
			calculate_vertex(&map->matrix[i][j], matrix_ret);
	}
}

void	calculate_vertex(t_vertex *v, double **matrix)
{
	int	x;
	int	y;
	int	z;
	int	w;

	x = v->vec->c[X];
	y = v->vec->c[Y];
	z = v->vec->c[Z];
	w = v->vec->c[W];
	v->vec->c[X] = matrix[0][0] * x + matrix[0][1] * \
	y + matrix[0][2] * z + matrix[0][3] * w;
	v->vec->c[Y] = matrix[1][0] * x + matrix[1][1] * \
	y + matrix[1][2] * z + matrix[1][3] * w;
	v->vec->c[Z] = matrix[2][0] * x + matrix[2][1] * \
	y + matrix[2][2] * z + matrix[2][3] * w;
	v->vec->c[W] = matrix[3][0] * x + matrix[3][1] * \
	y + matrix[3][2] * z + matrix[3][3] * w;
}

void	copy_matrix_values(t_map *map, t_vertex ***m1, t_vertex ***m2)
{
	int			i;
	int			j;
	t_vertex	**dst;
	t_vertex	**src;

	dst = *m1;
	src = *m2;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			dst[i][j].vec->c[X] = src[i][j].vec->c[X];
			dst[i][j].vec->c[Y] = src[i][j].vec->c[Y];
			dst[i][j].vec->c[Z] = src[i][j].vec->c[Z];
			dst[i][j].vec->c[W] = src[i][j].vec->c[W];
			dst[i][j].r = src[i][j].r;
			dst[i][j].g = src[i][j].g;
			dst[i][j].b = src[i][j].b;
		}
	}
}
