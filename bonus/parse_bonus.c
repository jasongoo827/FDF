/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:46:46 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/12 12:46:48 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_map	*init_map(char *argv)
{
	t_map	*map;
	int		fd;
	char	***db;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		exit_error(MERR);
	init_map_info(map);
	db = (char ***)malloc(sizeof(char **) * CPPPMAX);
	if (db == NULL)
		exit_error(MERR);
	fd = open(argv, O_RDONLY);
	check_error(fd, -1);
	read_fdf_file(map, fd, db);
	alloc_matrix(map);
	parse_matrix(map, db);
	normalize_matrix_value(map);
	dup_matrix(map);
	alloc_lookat_matrix(map);
	free_db(map, db);
	check_error(close(fd), -1);
	return (map);
}

void	read_fdf_file(t_map *map, int fd, char ***db)
{
	char	*line;
	char	**strs;
	char	***tmp;

	tmp = db;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		cut_newline(&line);
		strs = ft_split(line, ' ');
		check_width(map, strs);
		*tmp = strs;
		tmp++;
		map->height++;
		free(line);
	}
}

void	check_width(t_map *map, char **strs)
{
	int	i;
	int	width;

	i = -1;
	width = 0;
	while (strs[++i] != NULL && *strs[i] != '\n')
		width++;
	if (map->width == 0)
		map->width = width;
	else
	{
		if (map->width != width)
			exit_error(MAPERR);
	}
}

void	alloc_matrix(t_map *map)
{
	int	i;
	int	j;

	map->matrix = (t_vertex **)malloc(sizeof(t_vertex *) * (map->height));
	if (map->matrix == NULL)
		exit_error(MERR);
	i = -1;
	while (++i < map->height)
	{
		map->matrix[i] = (t_vertex *)malloc(sizeof(t_vertex) * (map->width));
		if (map->matrix[i] == NULL)
			exit_error(MERR);
		j = -1;
		while (++j < map->width)
		{
			map->matrix[i][j].vec = (t_vector *)malloc(sizeof(t_vector));
			if (map->matrix[i][j].vec == NULL)
				exit_error(MERR);
		}
	}
}

void	parse_matrix(t_map *map, char ***db)
{
	int		i;
	int		j;
	int		z;

	i = -1;
	map->max_z = MIN_INT;
	while (++i < map->height)
	{
		j = -1;
		while (db[i][++j] != NULL)
		{
			if (*db[i][j] == '\n')
				continue ;
			map->matrix[i][j].vec->c[X] = i;
			map->matrix[i][j].vec->c[Y] = j;
			z = ft_atoi(db[i][j]);
			if (z > map->max_z)
				map->max_z = z;
			map->matrix[i][j].vec->c[Z] = -(double)z;
			parse_color(&map->matrix[i][j], db[i][j]);
			map->matrix[i][j].vec->c[W] = 1;
		}
	}
}
