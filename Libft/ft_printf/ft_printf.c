/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:31:46 by jgoo              #+#    #+#             */
/*   Updated: 2023/11/20 12:31:49 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_init_lst(t_conv **lst)
{
	int	i;

	i = 0;
	while (i <= CONV_MAX)
	{
		lst[i] = (t_conv *)malloc(sizeof(t_conv));
		if (lst[i] == NULL)
			return (i);
		lst[i]->init = FALSE;
		lst[i]->mod_type = DEFAULT;
		lst[i]->f_left = FALSE;
		lst[i]->f_zero = FALSE;
		lst[i]->f_blank = FALSE;
		lst[i]->f_sharp = FALSE;
		lst[i]->f_sign = FALSE;
		lst[i]->f_width = FALSE;
		lst[i]->minwidth = -1;
		lst[i]->f_prec = FALSE;
		lst[i]->prec = -1;
		lst[i]->start = NULL;
		lst[i]->end = NULL;
		i++;
	}
	return (-1);
}

void	ft_free_lst(t_conv **lst, int idx)
{
	int	i;

	i = 0;
	while (i <= idx)
	{
		free(lst[i]);
		i++;
	}
	free(lst);
}

void	ft_parse_str(t_conv **lst, char *str)
{
	t_conv	*conv;

	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			ft_parse_conv(lst, &str);
		}
		else
		{
			conv = *lst;
			conv -> init = TRUE;
			conv -> mod_type = NORMAL;
			conv -> start = str;
			while (*str != '\0' && *str != '%')
				str++;
			conv -> end = str;
		}
		lst++;
	}
}

int	ft_write_str(t_conv **lst, va_list ap)
{
	int	i;
	int	tmp;
	int	ret;

	i = 0;
	ret = 0;
	while (lst[i]->init == TRUE)
	{
		tmp = write_by_type(lst[i], ap);
		if (tmp < 0)
			return (-1);
		ret += tmp;
		i++;
	}
	return (ret);
}
