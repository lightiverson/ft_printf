/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/09 10:17:02 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/05 15:13:48 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

/* Struct to unify data needed to handle %d, %i, %u, %U, %p, %x */
typedef struct s_data
{
	char	*a;
	char	*a_dup;
	size_t	a_len;
	int		a_digits;
	char	*b;
	char	*b_dup;
}	t_data;

/* Struct to unify data on format fields */
typedef struct s_fields
{
	int		count;
	_Bool	is_minus;
	char	padding_char;
	int		width;
	int		precision;
	char	conv_char;
}	t_fields;

/* ft_printf.c */
int			ft_printf(const char *fmt, ...);

/* set.c */
const char	*set_fields(const char *p_fmt, va_list ap, t_fields *fields);

/* format_s.c */
void		format_s(t_fields *fields, const char *sval);

/* format_c.c */
void		format_c(t_fields *fields, unsigned char cval);

/* format_d.c */
void		format_d(t_fields *fields, int dval);

/* format_u.c */
void		format_u(t_fields *fields, unsigned int uval);

/* format_x.c */
void		format_x(t_fields *fields, unsigned int xval);

/* format_p.c */
void		format_p(t_fields *fields, unsigned long pval);

/* precision_width_diuxp.c */
void		precision_diuxp(t_fields *fields, t_data *data);
void		width_diuxp(t_data *data, t_fields *fields);

/* utils.c */
int			is_nonzerodigit(int c);
int			get_alnum(char *s);
char		*str_toupper(char *str);
void		*zalloc(size_t count, size_t size, char c);

/* uitoa.c */
char		*uitoa(unsigned int n);

/* uitoa_hex.c */
char		*uitoa_hex(unsigned long n);

#	endif
