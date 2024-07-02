/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:45:08 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/12 12:45:09 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	draw_image(t_image *img, t_map *map)
{
	t_vertex	cur;
	t_vertex	next;
	int			i;
	int			j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (j + 1 < map->width)
			{
				cur = map->matrix[i][j];
				next = map->matrix[i][j + 1];
				bresenham(cur, next, img);
			}
			if (i + 1 < map->height)
			{
				cur = map->matrix[i][j];
				next = map->matrix[i + 1][j];
				bresenham(cur, next, img);
			}
		}
	}
}

void	bre_low_plus(t_vertex cur, t_vertex next, t_image *img)
{
	int	two_dy;
	int	two_dy_minux_dx;
	int	p;

	two_dy = 2 * abs(next.co.y - cur.co.y);
	two_dy_minux_dx = 2 * (abs(next.co.y - cur.co.y) \
	- abs(next.co.x - cur.co.x));
	p = 2 * (abs(next.co.y - cur.co.y) - abs(next.co.x - cur.co.x));
	put_pixel(img, cur);
	while (cur.co.x < next.co.x)
	{
		cur.co.x++;
		if (p < 0)
			p += two_dy;
		else
		{
			cur.co.y++;
			p += two_dy_minux_dx;
		}
		put_pixel(img, cur);
	}
}

void	bre_low_minus(t_vertex cur, t_vertex next, t_image *img)
{
	int	two_dy;
	int	two_dy_minux_dx;
	int	p;

	two_dy = 2 * abs(next.co.y - cur.co.y);
	two_dy_minux_dx = 2 * (abs(next.co.y - cur.co.y) \
	- abs(next.co.x - cur.co.x));
	p = 2 * (abs(next.co.y - cur.co.y) - abs(next.co.x - cur.co.x));
	put_pixel(img, cur);
	while (cur.co.x > next.co.x)
	{
		cur.co.x--;
		if (p < 0)
			p += two_dy;
		else
		{
			cur.co.y++;
			p += two_dy_minux_dx;
		}
		put_pixel(img, cur);
	}	
}

void	bre_high_plus(t_vertex cur, t_vertex next, t_image *img)
{
	int	two_dy;
	int	two_dy_minux_dx;
	int	p;

	two_dy = 2 * abs(next.co.x - cur.co.x);
	two_dy_minux_dx = 2 * (abs(next.co.x - cur.co.x) \
	- abs(next.co.y - cur.co.y));
	p = 2 * (abs(next.co.x - cur.co.x) - abs(next.co.y - cur.co.y));
	put_pixel(img, cur);
	while (cur.co.y < next.co.y)
	{
		cur.co.y++;
		if (p < 0)
			p += two_dy;
		else
		{
			cur.co.x++;
			p += two_dy_minux_dx;
		}
		put_pixel(img, cur);
	}
}

void	bre_high_minus(t_vertex cur, t_vertex next, t_image *img)
{
	int	two_dy;
	int	two_dy_minux_dx;
	int	p;

	two_dy = 2 * abs(next.co.x - cur.co.x);
	two_dy_minux_dx = 2 * (abs(next.co.x - cur.co.x) \
	- abs(next.co.y - cur.co.y));
	p = 2 * (abs(next.co.x - cur.co.x) - abs(next.co.y - cur.co.y));
	put_pixel(img, cur);
	while (cur.co.y < next.co.y)
	{
		cur.co.y++;
		if (p < 0)
			p += two_dy;
		else
		{
			cur.co.x--;
			p += two_dy_minux_dx;
		}
		put_pixel(img, cur);
	}
}
