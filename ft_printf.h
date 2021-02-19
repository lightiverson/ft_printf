/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/09 10:17:02 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/19 15:53:34 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdbool.h>

/*
** Struct to handle %d, %u.
** Zoek nog uit wat deze syntax precies doet.
*/

typedef struct s_data
{
	char *a;
	char *a_dup;
	size_t a_len;
	int a_digits;
	char *b;
	char *b_dup;
} t_data;

/*
** Struct to combine format fields.
*/

// typedef struct s_fields
struct		fields
{
	int		count;
	int		is_minus;
	char	padding_char;
	int		width;
	int		precision;
	char	conv_char;
};
// t_fields;

/*
** ft_printf prototype
*/
int			ft_printf(const char *fmt, ...);

/*
** set.c
*/
const char	*set_flags(const char *p_fmt, struct fields *fp);
const char	*set_precision(const char *p_fmt, va_list ap, struct fields *fp);
const char	*set_width(const char *p_fmt, struct fields *fp);
const char	*set_fields(const char *p_fmt, va_list ap, struct fields *fp);

/*
** format_s.c
*/
void		format_s(struct fields *fp, char *sval);

/*
** format_d.c
*/
void		precision_d(struct fields *fp, t_data *data);
void		width_d(t_data *data, struct fields *fp);
void		format_d(struct fields *fp, int dval);

/*
** format_c.c
*/
void		format_c(struct fields *fp, char cval);

/*
** format_u.c
*/
void		format_u(struct fields *fp, unsigned int uval);

/*
** utils.c
*/
int			is_nonzerodigit(int c);
void		*zalloc(size_t count, size_t size, char c);
int			get_digits(char *s);

# endif
