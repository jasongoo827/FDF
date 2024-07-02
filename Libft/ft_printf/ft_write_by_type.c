/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_by_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:47:49 by jgoo              #+#    #+#             */
/*   Updated: 2023/11/21 20:48:07 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_char(t_conv *conv, char c)
{
	char	*ret;
	int		res;

	ret = NULL;
	if (conv -> f_width == TRUE && conv -> minwidth > 0)
	{
		ret = fill_char(' ', conv -> minwidth);
		if (ret == NULL)
			return (-1);
		if (conv -> f_left == TRUE)
			ret[0] = c;
		else
			ret[conv -> minwidth - 1] = c;
		res = (int)write(1, ret, conv -> minwidth);
	}
	else
		res = (int)write(1, &c, 1);
	if (ret)
		free(ret);
	if (res < 0)
		return (-1);
	return (res);
}

int	type_str(t_conv *conv, char *str)
{
	char	*ret;
	int		maxlen;
	int		res;

	if (str == NULL)
		str = "(null)";
	maxlen = len_by_prec(conv, ft_strlen_pf(str));
	ret = fill_str(conv, str, maxlen);
	if (ret == NULL)
		return (-1);
	res = (int)write(1, ret, ft_strlen_pf(ret));
	if (res < 0)
	{
		free(ret);
		return (-1);
	}
	free(ret);
	return (res);
}

int	type_ptr(t_conv *conv, void *ptr)
{
	char	*ret[4];
	int		res;

	ret[1] = ft_strdup_pf("0x");
	ret[2] = ptr_to_str((uintptr_t)ptr, CHARSET_SHEX);
	ret[3] = add_padding(conv, ft_strlen_pf(ret[1]) + ft_strlen_pf(ret[2]));
	ret[0] = merge_str(conv, ret);
	if (ret[0] == NULL)
	{
		ft_abort_write(ret);
		return (-1);
	}
	res = (int)write(1, ret[0], ft_strlen_pf(ret[0]));
	ft_abort_write(ret);
	if (res < 0)
		return (-1);
	return (res);
}

int	type_dec(t_conv *conv, int n, char *charset)
{
	char	*ret[4];
	int		res;

	ret[1] = add_prefix(conv, n, charset);
	ret[2] = num_to_str(conv, n, ft_strlen_pf(charset), charset);
	ret[3] = add_padding(conv, ft_strlen_pf(ret[1]) + ft_strlen_pf(ret[2]));
	ret[0] = merge_str(conv, ret);
	if (ret[0] == NULL)
	{
		ft_abort_write(ret);
		return (-1);
	}
	res = (int)write(1, ret[0], ft_strlen_pf(ret[0]));
	ft_abort_write(ret);
	if (res < 0)
		return (-1);
	return (res);
}

int	type_udec(t_conv *conv, unsigned int n, char *charset)
{
	char	*ret[4];
	int		res;

	ret[1] = add_prefix(conv, n, charset);
	ret[2] = num_to_str(conv, n, ft_strlen_pf(charset), charset);
	ret[3] = add_padding(conv, ft_strlen_pf(ret[1]) + ft_strlen_pf(ret[2]));
	ret[0] = merge_str(conv, ret);
	if (ret[0] == NULL)
	{
		ft_abort_write(ret);
		return (-1);
	}
	res = (int)write(1, ret[0], ft_strlen_pf(ret[0]));
	ft_abort_write(ret);
	if (res < 0)
		return (-1);
	return (res);
}
