/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:51:42 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/07 15:51:43 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void	put_pixel(t_image *img, t_vertex vertex)
{
	char	*dst;
	int		x;
	int		y;

	x = vertex.co.x;
	y = vertex.co.y;
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + y * img->size_line + x * (img->bits_per_pixel / 8);
	*(int *)dst = create_argb(0, vertex.r, vertex.g, vertex.b);
}

void	bresenham(t_vertex cur, t_vertex next, t_image *img)
{
	cur.co.x = cur.vec->c[X];
	cur.co.y = cur.vec->c[Y];
	next.co.x = next.vec->c[X];
	next.co.y = next.vec->c[Y];
	if (abs(next.co.x - cur.co.x) > abs(next.co.y - cur.co.y))
		bre_low(cur, next, img);
	else
		bre_high(cur, next, img);
}

void	bre_low(t_vertex cur, t_vertex next, t_image *img)
{
	if (cur.co.x < next.co.x)
	{
		if (cur.co.y < next.co.y)
			bre_low_plus(cur, next, img);
		else
			bre_low_minus(next, cur, img);
	}
	else
	{
		if (cur.co.y < next.co.y)
			bre_low_minus(cur, next, img);
		else
			bre_low_plus(next, cur, img);
	}
}

void	bre_high(t_vertex cur, t_vertex next, t_image *img)
{
	if (cur.co.x < next.co.x)
	{
		if (cur.co.y < next.co.y)
			bre_high_plus(cur, next, img);
		else
			bre_high_minus(next, cur, img);
	}
	else
	{
		if (cur.co.y < next.co.y)
			bre_high_minus(cur, next, img);
		else
			bre_high_plus(next, cur, img);
	}
}
