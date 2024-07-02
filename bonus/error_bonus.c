/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:45:17 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/12 12:45:18 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	exit_error(char *s)
{
	check_error(write(2, s, ft_strlen(s)), -1);
	exit(1);
}

void	check_error(int ret, int target)
{
	if (ret == target)
	{
		check_error(write(2, strerror(errno), ft_strlen(strerror(errno))), -1);
		exit(0);
	}
}

void	check_input_error(int argc, char *argv)
{
	if (argc != 2)
		exit_error(AERR);
	if (check_fdf(argv) == 0)
		exit_error(FERR);
}

int	check_fdf(char *str)
{
	char	**strs;
	int		i;

	i = 0;
	strs = ft_split(str, '.');
	while (strs[i] != NULL)
		i++;
	if (ft_strncmp(strs[i - 1], "fdf", 4) == 0)
	{
		free_strs(strs);
		return (1);
	}
	free_strs(strs);
	return (0);
}
