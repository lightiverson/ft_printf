/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 14:35:22 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/06 11:21:20 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Initializes members of the t_fields *fields struct.

Precision is initiliazed to -1 because a precision of 0
will have consequences for formatting.

Width is initiliazed to 0 because a width of 0 won't have
consequences for formatting, but a width of 1 does.

t_fields *fields -- pointer to struct that contains information
	on fields
*/

static	void	init_fields(t_fields *fields)
{
	fields->count = 0;
	fields->is_minus = 0;
	fields->padding_char = ' ';
	fields->width = 0;
	fields->precision = -1;
	fields->conv_char = '\0';
}

/* Resets members of the t_fields *fields struct.

t_fields *fields -- pointer to struct that contains information
	on fields
*/

static	void	reset_fields(t_fields *fields)
{
	fields->is_minus = 0;
	fields->padding_char = ' ';
	fields->width = 0;
	fields->precision = -1;
	fields->conv_char = '\0';
}

/* Splits program flow up according to 
	conversion specifier.

va_list ap -- arguments pointer to list of unnamed arguments
t_fields *fields -- pointer to struct that contains information
	on fields
*/

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
		format_di(fields, va_arg(ap, int));
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

/* Iterates over const char *fmt.

Prints characters untill it finds a '%'.
After which it processes flags/fields/specifiers.
Then it prints the formatted variadic argument(s).
Lastly it resets the processed flags/fields/specifiers.

const char *fmt -- string to be formatted
va_list ap -- arguments pointer to list of unnamed arguments
t_fields *fields -- pointer to struct that contains information
	on fields
*/

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

/* Produces output according to a format.

ft_printf converts, formats and prints its arguements
on the standard output under control of the format. It
returns the number of characters printed.

It handles the '0' and '-' flags. It handles field with
and precision, also when given as arguments using '*'.
It handles the following specifiers: d, i, u, x, X, s, c, p.

const char *fmt -- string to be formatted
... -- variadic arguments
*/

int	ft_printf(const char *fmt, ...)
{
	va_list		ap;
	t_fields	fields;

	va_start(ap, fmt);
	interate_fmt(fmt, ap, &fields);
	va_end(ap);
	return (fields.count);
}
