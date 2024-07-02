/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:50:09 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/12 13:50:10 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rscale_transform(t_map *map)
{
	int		i;
	int		j;
	int		s_cnt;
	int		us_cnt;
	double	scale;

	i = -1;
	s_cnt = map->scale_cnt;
	us_cnt = map->uscale_cnt;
	scale = 1;
	while (s_cnt--)
		scale *= RATIO_P;
	while (us_cnt--)
		scale *= RATIO_M;
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

void	free_vector(t_vector *r0, t_vector *r1, t_vector *r2)
{
	free(r0);
	free(r1);
	free(r2);
}
