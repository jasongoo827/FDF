/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:42:49 by jgoo              #+#    #+#             */
/*   Updated: 2023/11/20 18:42:50 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isflag(char c)
{
	if (c == '-')
		return (1);
	else if (c == '0')
		return (1);
	else if (c == ' ')
		return (1);
	else if (c == '#')
		return (1);
	else if (c == '+')
		return (1);
	return (0);
}

t_mod	ft_istype(char c)
{
	if (c == TYPE_C)
		return (CHAR);
	else if (c == TYPE_S)
		return (STR);
	else if (c == TYPE_P)
		return (PTR);
	else if (c == TYPE_D || c == TYPE_I)
		return (SDEC);
	else if (c == TYPE_U)
		return (UDEC);
	else if (c == TYPE_SX)
		return (SHEX);
	else if (c == TYPE_BX)
		return (BHEX);
	else if (c == TYPE_PER)
		return (PER);
	return (ERR);
}

int	write_by_type(t_conv *conv, va_list ap)
{
	if (conv -> mod_type == NORMAL)
		return (type_normal(conv));
	else if (conv -> mod_type == CHAR)
		return (type_char(conv, va_arg(ap, int)));
	else if (conv -> mod_type == STR)
		return (type_str(conv, va_arg(ap, char *)));
	else if (conv -> mod_type == PTR)
		return (type_ptr(conv, va_arg(ap, void *)));
	else if (conv -> mod_type == SDEC)
		return (type_dec(conv, va_arg(ap, int), CHARSET_DEC));
	else if (conv -> mod_type == UDEC)
		return (type_udec(conv, va_arg(ap, unsigned int), CHARSET_DEC));
	else if (conv -> mod_type == SHEX)
		return (type_udec(conv, va_arg(ap, unsigned int), CHARSET_SHEX));
	else if (conv -> mod_type == BHEX)
		return (type_udec(conv, va_arg(ap, unsigned int), CHARSET_BHEX));
	else if (conv -> mod_type == PER)
		return (type_char(conv, '%'));
	return (-1);
}
