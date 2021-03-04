/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/07 14:33:30 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/04 12:29:27 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	const char	*set_flags(const char *p_fmt, t_fields *fields)
{
	while (*p_fmt == '-' || *p_fmt == '0')
	{
		if (*p_fmt == '-')
			fields->is_minus = 1;
		if (*p_fmt == '0')
			fields->padding_char = '0';
		p_fmt++;
	}
	return (p_fmt);
}

static	const char	*set_precision(const char *p_fmt, va_list ap,
		t_fields *fields)
{
	int	i;

	if (*p_fmt == '.')
	{
		p_fmt++;
		if (*p_fmt == '*')
		{
			i = va_arg(ap, int);
			if (i >= 0)
				fields->precision = i;
			p_fmt++;
		}
		else
		{
			if (*p_fmt == '-')
				p_fmt++;
			else
				fields->precision = atoi(p_fmt);
			while (isdigit(*p_fmt))
				p_fmt++;
		}
	}
	return (p_fmt);
}

static	const char	*set_width(const char *p_fmt, va_list ap, t_fields *fields)
{
	int	x;

	if (*p_fmt == '*')
	{
		x = va_arg(ap, int);
		if (x < 0)
		{
			fields->is_minus = 1;
			x = x * -1;
		}
		fields->width = x;
		p_fmt++;
	}
	else if (is_nonzerodigit(*p_fmt))
	{
		if (*p_fmt == '-')
		{
			fields->is_minus = 1;
			p_fmt++;
		}
		fields->width = atoi(p_fmt);
		while (isdigit(*p_fmt))
			p_fmt++;
	}
	return (p_fmt);
}

const char	*set_fields(const char *p_fmt, va_list ap, t_fields *fields)
{
	p_fmt++;
	if (*p_fmt == ' ')
	{
		write(1, " ", 1);
		while (isspace(*p_fmt))
			p_fmt++;
	}
	p_fmt = set_flags(p_fmt, fields);
	p_fmt = set_width(p_fmt, ap, fields);
	p_fmt = set_precision(p_fmt, ap, fields);
	fields->conv_char = *p_fmt;
	if (fields->padding_char == '0' && fields->is_minus)
		fields->padding_char = ' ';
	if (fields->padding_char == '0' && (fields->precision > -1 && (
				fields->conv_char == 'd' || fields->conv_char == 'u'
				|| fields->conv_char == 'x' || fields->conv_char == 'X'
				|| fields->conv_char == 'p' || fields->conv_char == 'i')))
	{
		fields->padding_char = ' ';
	}
	return (p_fmt);
}
