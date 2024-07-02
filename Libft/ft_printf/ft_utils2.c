/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:32:49 by jgoo              #+#    #+#             */
/*   Updated: 2023/11/24 19:32:51 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup_pf(char *s1)
{
	size_t		len;
	int			i;
	char		*ret;

	len = ft_strlen_pf(s1);
	i = 0;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strmerge(int n, ...)
{
	char	*tmp;
	char	*buf;
	int		i;
	va_list	ap;

	va_start(ap, n);
	buf = ft_strdup_pf("");
	if (buf == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		tmp = va_arg(ap, char *);
		if (ft_strappend(&buf, tmp) < 0)
		{
			free(buf);
			return (NULL);
		}
		i++;
	}
	va_end(ap);
	return (buf);
}

int	ft_strappend(char **s1, char *s2)
{
	char	*tmp;

	if (s2 == NULL)
		return (-1);
	tmp = ft_strjoin_pf(*s1, s2);
	if (tmp == NULL)
		return (-1);
	free(*s1);
	*s1 = tmp;
	return (1);
}

char	*ft_strjoin_pf(char const *s1, char const *s2)
{
	int		i;
	int		j;
	size_t	len;
	char	*ret;

	i = 0;
	j = 0;
	len = ft_strlen_pf(s1) + ft_strlen_pf(s2);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}
