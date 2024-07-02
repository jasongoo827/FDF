/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:48:06 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/12 12:48:07 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_vector	*set_vector(double x, double y, double z, double w)
{
	t_vector	*vector;

	vector = (t_vector *)malloc(sizeof(t_vector));
	if (vector == NULL)
		exit_error(MERR);
	vector->c[0] = x;
	vector->c[1] = y;
	vector->c[2] = z;
	vector->c[3] = w;
	return (vector);
}

t_vector	*normalize_vector1(t_vector *vector)
{
	t_vector	*n_vector;
	double		size;

	size = sqrt(pow(vector->c[X], 2) + pow(vector->c[Y], 2) \
	+ pow(vector->c[Z], 2));
	n_vector = set_vector(vector->c[0] / size, \
	vector->c[1] / size, vector->c[2] / size, 0);
	return (n_vector);
}

void	normalize_vector2(t_vector *vector)
{
	double		size;

	size = sqrt(pow(vector->c[X], 2) + pow(vector->c[Y], 2) \
	+ pow(vector->c[Z], 2));
	vector->c[X] = vector->c[X] / size;
	vector->c[Y] = vector->c[Y] / size;
	vector->c[Z] = vector->c[Z] / size;
}

t_vector	*cross_vector(t_vector *v1, t_vector *v2)
{
	t_vector	*c_vector;
	double		x;
	double		y;
	double		z;

	x = v1->c[Y] * v2->c[Z] - v1->c[Z] * v2->c[Y];
	y = v1->c[Z] * v2->c[X] - v1->c[X] * v2->c[Z];
	z = v1->c[X] * v2->c[Y] - v1->c[Y] * v2->c[X];
	c_vector = set_vector(x, y, z, 0);
	return (c_vector);
}

double	dot_vector(t_vector *v1, t_vector *v2)
{
	double		x;
	double		y;
	double		z;

	x = v1->c[X] * v2->c[X] * (-1);
	y = v1->c[Y] * v2->c[Y] * (-1);
	z = v1->c[Z] * v2->c[Z] * (-1);
	return (x + y + z);
}
