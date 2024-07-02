/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:14:10 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/07 16:14:11 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_db(t_map *map, char ***db)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (db[i][++j] != NULL)
			free(db[i][j]);
		free(db[i]);
	}
	free(db);
}

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i] != NULL)
		free(strs[i]);
	free(strs);
}

void	alloc_lookat_matrix(t_map *map)
{
	map->la_matrix = (t_lookat_matrix *)malloc(sizeof(t_lookat_matrix));
	if (map->la_matrix == NULL)
		exit_error(MERR);
	map->la_matrix->eye_position = set_vector(1, 1, -1, 1);
	map->la_matrix->eye_direction = set_vector(-1, -1, 1, 0);
	map->la_matrix->up_direction = set_vector(0, 1, 0, 0);
	map->la_matrix->matrix = alloc_dmatrix(4);
	map->la_matrix->r_matrix = alloc_dmatrix(4);
}

double	**alloc_dmatrix(int n)
{
	double	**matrix;
	int		i;

	matrix = (double **)malloc(sizeof(double *) * n);
	if (matrix == NULL)
		exit_error(MERR);
	i = -1;
	while (++i < 4)
	{
		matrix[i] = (double *)malloc(sizeof(double) * n);
		if (matrix[i] == NULL)
			exit_error(MERR);
	}	
	return (matrix);
}

void	mul_matrix(double **m1, double **m2, double **ret)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			ret[i][j] = 0;
			k = -1;
			while (++k < 4)
				ret[i][j] += m1[i][k] * m2[k][j];
		}
	}
}
