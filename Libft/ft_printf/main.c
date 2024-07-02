/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:00:11 by jgoo              #+#    #+#             */
/*   Updated: 2023/12/14 20:00:12 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	t_conv	**lst;
	va_list	ap;
	int		res;
	int		idx;

	va_start(ap, str);
	lst = (t_conv **)malloc(sizeof(t_conv *) * (CONV_MAX + 1));
	if (lst == NULL)
		return (-1);
	idx = ft_init_lst(lst);
	if (idx >= 0)
	{
		ft_free_lst(lst, idx);
		return (-1);
	}
	ft_parse_str(lst, (char *)str);
	res = ft_write_str(lst, ap);
	ft_free_lst(lst, CONV_MAX);
	va_end(ap);
	return (res);
}
