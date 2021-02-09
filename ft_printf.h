/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/09 10:17:02 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/09 10:48:03 by kawish        ########   odam.nl         */
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
** struct
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
int			count_chars(int n);
int			count_digits(int n);
char*		precision_d(struct fields *fp, int dval, char *a, int chars_a);
char*		width_d(struct fields *fp, int dval, char *a, int chars_a);
void		format_d(struct fields *fp, int dval);

/*
** utils.c
*/
int			is_nonzerodigit(int c);
void		print_fields(struct fields *f);

# endif
