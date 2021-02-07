/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 14:35:22 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/07 14:33:49 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		init_fields(struct fields *fp)
{
	fp->is_minus = 0;
	fp->padding_char = ' ';
	fp->width = 0;
	fp->precision = -1;
	fp->conv_char = '\0';
}

void		format(va_list ap, struct fields *fp)
{
	char			*sval;
	int				dval;

	if (fp->conv_char == 's')
	{
		sval = va_arg(ap, char*);
		if (sval == NULL)
			format_s(fp, "(null)");
		else
			format_s(fp, sval);
	}
	else if (fp->conv_char == 'd')
	{
		dval = va_arg(ap, int);
		format_d(fp, dval);
	}
}

int			interate_fmt(const char *fmt, va_list ap, struct fields *fp)
{
	const char		*p_fmt;

	p_fmt = fmt;
	init_fields(fp);
	while (*p_fmt)
	{
		if (*p_fmt != '%')
			write(1, p_fmt, 1);
		else
		{
			p_fmt = set_fields(p_fmt, ap, fp);
			format(ap, fp);
		}
		p_fmt++;
	}
	return (0);
}

int			ft_printf(const char *fmt, ...)
{
	va_list			ap;
	struct fields	f;
	int				n;

	va_start(ap, fmt);
	n = interate_fmt(fmt, ap, &f);
	va_end(ap);
	return (n);
}
