/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:54:58 by jgoo              #+#    #+#             */
/*   Updated: 2023/11/21 20:55:10 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*fill_char(char c, int len)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}

char	*fill_str(t_conv *conv, char *str, int len)
{
	char	*ret;
	int		res;
	char	*padding;

	padding = add_padding(conv, len);
	if (padding == NULL)
		return (NULL);
	ret = ft_substr_pf(str, len);
	if (ret == NULL)
	{
		free(padding);
		return (NULL);
	}
	res = fill_str_by_left(conv, &ret, padding);
	if (res < 0)
		return (NULL);
	return (ret);
}

int	len_by_prec(t_conv *conv, int len)
{
	if (conv -> f_prec == TRUE && conv -> prec >= 0)
	{
		if (len > conv -> prec)
			len = conv -> prec;
	}
	return (len);
}

char	*str_padding(t_conv *conv, int maxlen)
{
	if (conv -> f_width == TRUE && conv -> minwidth > maxlen)
		return (fill_char(' ', conv -> minwidth - maxlen));
	else
		return (ft_strdup_pf(""));
}

int	ft_numlen(uintptr_t num, int l)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num /= l;
		len++;
	}
	return (len);
}
