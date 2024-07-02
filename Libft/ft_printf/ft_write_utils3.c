/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:15:18 by jgoo              #+#    #+#             */
/*   Updated: 2023/11/27 14:15:21 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*merge_str(t_conv *conv, char **ret)
{
	if (ret[3] != NULL && ret[3][0] == '0')
		return (ft_strmerge(3, ret[1], ret[3], ret[2]));
	else
	{
		if (conv -> f_left == TRUE)
			return (ft_strmerge(3, ret[1], ret[2], ret[3]));
		else
			return (ft_strmerge(3, ret[3], ret[1], ret[2]));
	}
}

void	ft_abort_write(char **ret)
{
	int	rep;
	int	i;

	rep = 4;
	i = 0;
	while (i < rep)
	{
		if (ret[i] != NULL)
			free(ret[i]);
		i++;
	}
}

char	*prefix_sign(t_conv *conv, intptr_t n)
{
	if (n >= 0)
	{
		if (conv -> mod_type != SDEC)
			return (ft_strdup_pf(""));
		if (conv -> f_blank == true)
			return (ft_strdup_pf(" "));
		else if (conv -> f_sign == true)
			return (ft_strdup_pf("+"));
		return (ft_strdup_pf(""));
	}
	return (ft_strdup_pf("-"));
}

int	prefix_hex(t_conv *conv, int base, intptr_t num, char **buf)
{
	if (base == 16 && conv -> f_sharp == true && num != 0)
	{
		if (conv -> mod_type == SHEX && ft_strappend(buf, "0x") < 0)
			return (-1);
		if (conv -> mod_type == BHEX && ft_strappend(buf, "0X") < 0)
			return (-1);
	}
	return (1);
}

int	prefix_prec(t_conv *conv, int base, intptr_t n, char **buf)
{
	int		numlen;
	char	*tmp;
	int		res;

	numlen = 0;
	if (conv -> f_prec == true && conv -> prec > 0)
	{
		numlen = ft_numlen(n, base);
		if (conv -> prec > numlen)
		{
			tmp = fill_char('0', conv -> prec - numlen);
			if (tmp == NULL)
				return (-1);
			res = ft_strappend(buf, tmp);
			free(tmp);
			if (res < 0)
				return (-1);
		}
	}
	return (1);
}
