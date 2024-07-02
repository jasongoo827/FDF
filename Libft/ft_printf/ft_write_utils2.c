/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:30:29 by jgoo              #+#    #+#             */
/*   Updated: 2023/11/24 14:30:31 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ptr_to_str(uintptr_t num, char *charset)
{
	char	*str;
	int		len;
	int		i;

	if (ft_numlen(num, ft_strlen_pf(charset)) == 0)
		return (ft_strdup_pf("0"));
	len = ft_numlen(num, ft_strlen_pf(charset));
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = len - 1;
	while (i >= 0)
	{
		str[i--] = charset[num % 16];
		num /= 16;
	}
	str[len] = '\0';
	return (str);
}

char	*num_to_str(t_conv *conv, intptr_t num, int base, char *charset)
{
	char	*str;
	int		len;
	int		i;

	if (num == 0)
	{
		if (conv -> f_prec == TRUE)
			return (ft_strdup_pf(""));
		else
			return (ft_strdup_pf("0"));
	}
	if (num < 0)
		num *= -1;
	len = ft_numlen(num, base);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = len - 1;
	while (num != 0)
	{
		str[i--] = charset[num % base];
		num /= base;
	}
	str[len] = '\0';
	return (str);
}

int	fill_str_by_left(t_conv *conv, char **ret, char *padding)
{
	char	*tmp;
	int		res;

	tmp = NULL;
	if (conv -> f_left == FALSE)
	{
		tmp = *ret;
		*ret = padding;
		padding = tmp;
	}
	res = ft_strappend(ret, padding);
	free(padding);
	if (res < 0)
	{
		free(*ret);
		return (-1);
	}
	return (1);
}

char	*add_prefix(t_conv *conv, intptr_t n, char *charset)
{
	char	*buf;

	buf = prefix_sign(conv, n);
	if (buf == NULL)
		return (NULL);
	if (n < 0)
		n *= -1;
	if (prefix_hex(conv, ft_strlen_pf(charset), n, &buf) < 0)
	{
		free(buf);
		return (NULL);
	}
	if (prefix_prec(conv, ft_strlen_pf(charset), n, &buf) < 0)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

char	*add_padding(t_conv *conv, int len)
{
	char	*pad;
	int		len_pad;

	len_pad = 0;
	if (conv ->f_width == true && conv -> minwidth > len)
		len_pad = conv -> minwidth - len;
	if (conv -> f_zero && !conv -> f_prec && !conv -> f_left)
		pad = fill_char('0', len_pad);
	else
		pad = fill_char(' ', len_pad);
	if (pad == NULL)
		return (NULL);
	return (pad);
}
