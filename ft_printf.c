/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 14:35:22 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/05 14:01:34 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	init_fields(t_fields *fields)
{
	fields->count = 0;
	fields->is_minus = 0;
	fields->padding_char = ' ';
	fields->width = 0;
	fields->precision = -1;
	fields->conv_char = '\0';
}

static	void	reset_fields(t_fields *fields)
{
	fields->is_minus = 0;
	fields->padding_char = ' ';
	fields->width = 0;
	fields->precision = -1;
	fields->conv_char = '\0';
}

static	void	format(va_list ap, t_fields *fields)
{
	const char		*sval;

	if (fields->conv_char == 's')
	{
		sval = va_arg(ap, char *);
		if (sval == NULL)
			format_s(fields, "(null)");
		else
			format_s(fields, sval);
	}
	else if (fields->conv_char == 'd' || fields->conv_char == 'i')
		format_d(fields, va_arg(ap, int));
	else if (fields->conv_char == 'c')
		format_c(fields, va_arg(ap, int));
	else if (fields->conv_char == 'u')
		format_u(fields, va_arg(ap, unsigned int));
	else if (fields->conv_char == 'x' || fields->conv_char == 'X')
		format_x(fields, va_arg(ap, unsigned int));
	else if (fields->conv_char == 'p')
		format_p(fields, va_arg(ap, unsigned long));
	else if (fields->conv_char == '%')
		format_c(fields, '%');
}

static	void	interate_fmt(const char *fmt, va_list ap, t_fields *fields)
{
	const char		*p_fmt;

	p_fmt = fmt;
	init_fields(fields);
	while (*p_fmt)
	{
		if (*p_fmt != '%')
		{
			write(1, p_fmt, 1);
			fields->count++;
		}
		else
		{
			p_fmt = set_fields(p_fmt, ap, fields);
			format(ap, fields);
			reset_fields(fields);
		}
		p_fmt++;
	}
}

int	ft_printf(const char *fmt, ...)
{
	va_list		ap;
	t_fields	fields;

	va_start(ap, fmt);
	interate_fmt(fmt, ap, &fields);
	va_end(ap);
	return (fields.count);
}
