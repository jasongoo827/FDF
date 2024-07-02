/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:24:11 by jgoo              #+#    #+#             */
/*   Updated: 2023/11/15 16:24:13 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define TYPE_C 'c'
# define TYPE_S 's'
# define TYPE_P 'p'
# define TYPE_D 'd'
# define TYPE_I 'i'
# define TYPE_U 'u'
# define TYPE_SX 'x'
# define TYPE_BX 'X'
# define TYPE_PER '%'
# define CHARSET_DEC "0123456789"
# define CHARSET_SHEX "0123456789abcdef"
# define CHARSET_BHEX "0123456789ABCDEF"
# define CONV_MAX 512
# define PRINT_MAX 100000
# define MAXLONG 9223372036854775807

typedef enum e_mod
{
	DEFAULT = 0,
	NORMAL,
	CHAR,
	STR,
	PTR,
	SDEC,
	UDEC,
	SHEX,
	BHEX,
	PER,
	ERR
}	t_mod;

typedef struct s_conv
{
	bool	init;
	bool	f_left;
	bool	f_zero;
	bool	f_blank;
	bool	f_sharp;
	bool	f_sign;
	bool	f_width;
	int		minwidth;
	bool	f_prec;
	int		prec;
	char	*start;
	char	*end;
	t_mod	mod_type;
}	t_conv;

int		ft_printf(const char *str, ...);
int		ft_init_lst(t_conv **lst);
void	ft_parse_str(t_conv **lst, char *str);
int		ft_write_str(t_conv **lst, va_list ap);
void	ft_free_lst(t_conv **lst, int idx);
void	ft_parse_conv(t_conv **lst, char **s);
void	parse_flag(t_conv *lst, char **s);
void	parse_width(t_conv *lst, char **s);
void	parse_prec(t_conv *lst, char **s);
void	parse_type(t_conv *lst, char **s);
int		ft_isflag(char c);
t_mod	ft_istype(char c);
int		write_by_type(t_conv *conv, va_list ap);
int		type_char(t_conv *conv, char c);
int		type_str(t_conv *conv, char *str);
int		type_ptr(t_conv *conv, void *ptr);
int		type_dec(t_conv *conv, int n, char *charset);
int		type_udec(t_conv *conv, unsigned int n, char *charset);
int		type_normal(t_conv *conv);
char	*fill_char(char c, int len);
char	*fill_str(t_conv *conv, char *str, int len);
int		len_by_prec(t_conv *conv, int len);
char	*str_padding(t_conv *conv, int maxlen);
int		ft_numlen(uintptr_t num, int l);
char	*ptr_to_str(uintptr_t num, char *charset);
char	*num_to_str(t_conv *conv, intptr_t num, int base, char *charset);
int		fill_str_by_left(t_conv *conv, char **s1, char *s2);
char	*add_prefix(t_conv *conv, intptr_t n, char *charset);
char	*add_padding(t_conv *conv, int len);
char	*merge_str(t_conv *conv, char **ret);
void	ft_abort_write(char **ret);
char	*prefix_sign(t_conv *conv, intptr_t n);
int		prefix_hex(t_conv *conv, int base, intptr_t num, char **buf);
int		prefix_prec(t_conv *conv, int base, intptr_t n, char **buf);
size_t	ft_strlen_pf(const char *s);
int		ft_isdigit_pf(int c);
int		ft_cast_pf(unsigned long long ret, int sign);
int		ft_atoi_pf(const char *str);
char	*ft_substr_pf(char *str, int len);
char	*ft_strdup_pf(char *s1);
char	*ft_strmerge(int n, ...);
int		ft_strappend(char **s1, char *s2);
char	*ft_strjoin_pf(char const *s1, char const *s2);

#endif
