/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:02:46 by jgoo              #+#    #+#             */
/*   Updated: 2023/12/14 20:02:49 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_conv(t_conv **lst, char **s)
{
	t_conv	*conv;

	conv = *lst;
	conv -> init = TRUE;
	parse_flag(*lst, s);
	parse_width(*lst, s);
	parse_prec(*lst, s);
	parse_type(*lst, s);
}

void	parse_flag(t_conv *lst, char **s)
{
	while (ft_isflag(**s) == TRUE)
	{
		if (**s == '-')
			lst -> f_left = TRUE;
		else if (**s == '0')
			lst -> f_zero = TRUE;
		else if (**s == ' ')
			lst -> f_blank = TRUE;
		else if (**s == '#')
			lst -> f_sharp = TRUE;
		else if (**s == '+')
			lst -> f_sign = TRUE;
		(*s)++;
	}
}

void	parse_width(t_conv *lst, char **s)
{
	if (ft_isdigit_pf(**s) == TRUE)
	{
		lst -> f_width = TRUE;
		lst -> minwidth = ft_atoi_pf(*s);
		while (ft_isdigit_pf(**s) == TRUE)
			(*s)++;
	}
}

void	parse_prec(t_conv *lst, char **s)
{
	if (**s != '.')
		return ;
	else
	{
		lst -> f_prec = TRUE;
		lst -> prec = 0;
	}
	(*s)++;
	if (ft_isdigit_pf(**s) == TRUE)
	{
		lst -> prec = ft_atoi_pf(*s);
		while (ft_isdigit_pf(**s) == TRUE)
			(*s)++;
	}
}

void	parse_type(t_conv *lst, char **s)
{
	if (ft_istype(**s) != ERR)
		lst -> mod_type = ft_istype(**s);
	else
		lst -> mod_type = ERR;
	(*s)++;
}
