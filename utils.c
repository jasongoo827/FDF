/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:02:31 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/07 16:02:32 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_str_digit(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (0);
	if (str[0] == '-')
	{
		if (str[1] == '\0')
			return (0);
		while (str[++i] != '\0')
		{
			if (ft_isdigit(str[i] - '0') == 0)
				return (0);
		}
		return (1);
	}
	i = -1;
	while (str[++i] != '\0')
	{
		if (ft_isdigit(str[i] - '0') == 0)
			return (0);
	}
	return (1);
}

int	check_str_int(char *str)
{
	int			i;
	long long	ret;
	int			sign;

	i = 0;
	ret = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	if (ret * sign > (long long)MAX_INT || ret * sign < (long long)MIN_INT)
		return (0);
	return (1);
}

void	dup_matrix(t_map *map)
{
	int	i;
	int	j;

	map->back_up = (t_vertex **)malloc(sizeof(t_vertex *) * (map->height));
	if (map->back_up == NULL)
		exit_error(MERR);
	i = -1;
	while (++i < map->height)
	{
		map->back_up[i] = (t_vertex *)malloc(sizeof(t_vertex) * (map->width));
		if (map->back_up[i] == NULL)
			exit_error(MERR);
		j = -1;
		while (++j < map->width)
		{
			map->back_up[i][j].vec = (t_vector *)malloc(sizeof(t_vector));
			if (map->back_up[i][j].vec == NULL)
				exit_error(MERR);
		}
	}
}

void	calculate_scale(t_map *map)
{
	int	scale;

	scale = SCALE;
	while (map->width * scale > WIN_W)
		scale--;
	while (map->height * scale > WIN_H)
		scale--;
	while ((map->max_x - map->min_x) * scale > WIN_W)
		scale--;
	while ((map->max_y - map->min_y) * scale > WIN_H)
		scale--;
	map->scale = scale;
}

void	calculate_start_trans(t_map *map, int dst_x, int dst_y)
{
	map->start_x_trans = dst_x - (map->max_x + map->min_x) / 2;
	map->start_y_trans = dst_y - (map->max_y + map->min_y) / 2;
}
