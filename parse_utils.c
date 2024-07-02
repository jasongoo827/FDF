/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:59:59 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/07 16:00:03 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_color(t_vertex *vertex, char *str)
{
	char	**strs;
	int		i;

	if (check_str_digit(str) && check_str_int(str))
	{
		vertex->r = 255;
		vertex->g = 255;
		vertex->b = 255;
		return ;
	}
	strs = ft_split(str, ',');
	i = 0;
	while (strs[i] != NULL)
		i++;
	if (i != 2)
		exit_error(MAPERR);
	if (!check_str_digit(strs[0]) || !check_str_int(strs[0]))
		exit_error(MAPERR);
	if ((ft_strlen(strs[1]) != COLOR_LEN && ft_strlen(strs[1]) != 6 \
	&& ft_strlen(strs[1]) != 4) || !check_hex(strs[1]))
		exit_error(MAPERR);
	parse_rgb(vertex, strs[1], ft_strlen(strs[1]));
	free_strs(strs);
}

void	parse_rgb(t_vertex *vertex, char *str, int len)
{
	if (len == 4)
	{
		vertex->r = 0;
		vertex->g = 0;
		vertex->b = (str[2] - '0') * HEX_LEN + (str[3] - '0');
	}
	else if (len == 6)
	{
		vertex->r = 0;
		vertex->g = (str[2] - '0') * HEX_LEN + (str[3] - '0');
		vertex->b = (str[4] - '0') * HEX_LEN + (str[5] - '0');
	}
	else if (len == 8)
	{
		vertex->r = (str[2] - '0') * HEX_LEN + (str[3] - '0');
		vertex->g = (str[4] - '0') * HEX_LEN + (str[5] - '0');
		vertex->b = (str[6] - '0') * HEX_LEN + (str[7] - '0');
	}
}

int	check_hex(char *str)
{
	int	i;

	if (ft_strncmp(str, "0x", 2) != 0)
		return (0);
	i = 1;
	while (str[++i] != '\0')
	{
		if (str[i] - '0' < 0 || str[i] - '0' > 9)
		{
			if (str[i] >= 'a' && str[i] >= 'z')
			{
				if (str[i] - 'a' < 0 || str[i] - 'a' > 5)
					return (0);
			}
			else if (str[i] >= 'A' && str[i] <= 'Z')
			{
				if (str[i] - 'A' < 0 || str[i] - 'A' > 5)
					return (0);
			}
		}
	}
	return (1);
}

void	cut_newline(char **line)
{
	char	*tmp;
	char	*str;

	tmp = NULL;
	str = *line;
	if (str[ft_strlen(str) - 1] == '\n')
	{
		tmp = ft_substr(str, 0, ft_strlen(str) - 1);
		if (tmp == NULL)
			exit_error(MERR);
		free(str);
		*line = tmp;
	}
}

void	free_dmatrix(double **matrix)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(matrix[i]);
	free(matrix);
}
