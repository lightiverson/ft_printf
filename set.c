/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/07 14:33:30 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/11 15:23:31 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*set_flags(const char *p_fmt, struct fields *fp)
{
	while (*p_fmt == '-' || *p_fmt == '0')
	{
		if (*p_fmt == '-')
			fp->is_minus = 1;
		if (*p_fmt == '0')
			fp->padding_char = '0';
		p_fmt++;
	}
	return (p_fmt);
}

const char	*set_precision(const char *p_fmt, va_list ap, struct fields *fp)
{
	int i;

	if (*p_fmt == '.')
	{
		p_fmt++;
		if (*p_fmt == '*')
		{
			i = va_arg(ap, int);
			if (i >= 0)
				fp->precision = i;
			p_fmt++;
		}
		else
		{
			if (*p_fmt == '-')
				p_fmt++;
			else
				fp->precision = atoi(p_fmt);
			while (isdigit(*p_fmt))
				p_fmt++;
		}
	}
	return (p_fmt);
}

const char	*set_width(const char *p_fmt, struct fields *fp)
{
	if (is_nonzerodigit(*p_fmt))
	{
		if (*p_fmt == '-')
		{
			fp->is_minus = 1;
			p_fmt++;
		}
		fp->width = atoi(p_fmt);
		while (isdigit(*p_fmt))
			p_fmt++;
	}
	return (p_fmt);
}

const char	*set_fields(const char *p_fmt, va_list ap, struct fields *fp)
{
	p_fmt++;
	p_fmt = set_flags(p_fmt, fp);
	p_fmt = set_width(p_fmt, fp);
	p_fmt = set_precision(p_fmt, ap, fp);
	fp->conv_char = *p_fmt;
	if (fp->padding_char == '0' && fp->is_minus)
		fp->padding_char = ' ';
	if ( fp->padding_char == '0' && (fp->precision > -1 && (fp->conv_char == 'd' || fp->conv_char == 'u')))
		fp->padding_char = ' ';
	return (p_fmt);
}
