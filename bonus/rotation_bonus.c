/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:47:02 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/12 12:47:03 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	init_rx_matrix(double **matrix, double angle)
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = cos(angle);
	matrix[1][2] = sin(angle);
	matrix[1][3] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = -sin(angle);
	matrix[2][2] = cos(angle);
	matrix[2][3] = 0;
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}

void	init_ry_matrix(double **matrix, double angle)
{
	matrix[0][0] = cos(angle);
	matrix[0][1] = 0;
	matrix[0][2] = -sin(angle);
	matrix[0][3] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[1][3] = 0;
	matrix[2][0] = sin(angle);
	matrix[2][1] = 0;
	matrix[2][2] = cos(angle);
	matrix[2][3] = 0;
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}

void	init_rz_matrix(double **matrix, double angle)
{
	matrix[0][0] = cos(angle);
	matrix[0][1] = sin(angle);
	matrix[0][2] = 0;
	matrix[0][3] = 0;
	matrix[1][0] = -sin(angle);
	matrix[1][1] = cos(angle);
	matrix[1][2] = 0;
	matrix[1][3] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	matrix[2][3] = 0;
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}

void	normalize_matrix_value(t_map *map)
{
	double	size;
	int		i;
	int		j;

	size = 1.0;
	if (map->max_z >= 10 && map->max_z < 50)
		size = 0.5;
	else if (map->max_z >= 50 && map->max_z < 100)
		size = 0.25;
	else if (map->max_z >= 100)
		size = 0.125;
	else if (map->max_z < 10)
		return ;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
			map->matrix[i][j].vec->c[Z] *= size;
	}
}

void	init_map_info(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->scale_cnt = 0;
	map->uscale_cnt = 0;
	map->start_x = WIN_W / 2;
	map->start_y = WIN_H / 2;
	map->start_rot_x = 0;
	map->start_rot_y = M_PI / 6;
	map->start_rot_z = 0;
}
