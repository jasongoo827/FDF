/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:58:53 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/07 15:58:54 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_transform(t_map *map, double scale)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			map->matrix[i][j].vec->c[X] *= scale;
			map->matrix[i][j].vec->c[Y] *= scale;
			map->matrix[i][j].vec->c[Z] *= scale;
		}
	}
}

void	translate_transform(t_map *map, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			map->matrix[i][j].vec->c[X] += x;
			map->matrix[i][j].vec->c[Y] += y;
		}
	}
}

void	change_direction(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
			map->matrix[i][j].vec->c[Y] *= -1;
	}
}

void	calculate_max(t_map *map)
{
	map->max_x = (int)map->matrix[0][map->width - 1].vec->c[X];
	map->max_y = (int)map->matrix[0][map->width - 1].vec->c[Y];
	map->min_x = (int)map->matrix[map->height - 1][0].vec->c[X];
	map->min_y = (int)map->matrix[map->height - 1][0].vec->c[Y];
}
