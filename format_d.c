/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 14:51:41 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/09 11:04:37 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			count_chars(int n)
{
	int		c;

	c = 0;
	if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		n = n * -1;
		c++;
	}
	while (n > 9)
	{
		c++;
		n = n / 10;
	}
	c++;
	return (c);
}

int			count_digits(int n)
{
	int		c;

	c = 0;
	if (n == -2147483648)
		return (10);
	else if (n < 0)
	{
		n = n * -1;
	}
	while (n > 9)
	{
		c++;
		n = n / 10;
	}
	c++;
	return (c);
}

char		*precision_d(struct fields *fp, int dval, char *a, int chars_a)
{
	int		digits_a;
	char	ret[fp->precision + chars_a + 1];
	char	*p_ret;

	digits_a = count_digits(dval);
	p_ret = ret;
	memset(ret, '0', sizeof(ret));
	if (dval < 0)
	{
		*p_ret++ = '-';
		a++;
	}
	strlcpy(p_ret + (fp->precision - digits_a), a, strlen(p_ret) + 1);
	return (ft_strdup(ret));
}

char		*width_d(struct fields *fp, int dval, char *a, int chars_a)
{
	char	ret[fp->width + chars_a + 1];
	char	*p_ret;

	p_ret = ret;
	memset(ret, fp->padding_char, sizeof(ret));
	if (fp->is_minus)
		memcpy(ret, a, strlen(a));
	else
	{
		if (dval < 0 && fp->padding_char == '0')
		{
			*p_ret++ = '-';
			a++;
		}
		memcpy(p_ret + (fp->width - chars_a), a, strlen(a));
	}
	ret[fp->width] = '\0';
	return (ft_strdup(ret));
}

void		format_d(struct fields *fp, int dval)
{
	char			*a;
	int				digits_a;
	int				chars_a;

	a = ft_itoa(dval);
	if (!a)
		return ;
	digits_a = count_digits(dval);
	chars_a = count_chars(dval);
	if (fp->precision >= 0 && digits_a < fp->precision)
	{
		a = precision_d(fp, dval, a, chars_a);
		chars_a = (int)strlen(a);
	}
	else if (fp->precision == 0 && dval == 0)
	{
		memset(a, '\0', strlen(a) + 1);
		chars_a = (int)strlen(a);
	}
	if (chars_a < fp->width)
		a = width_d(fp, dval, a, chars_a);
	fp->count = fp->count + strlen(a);
	ft_putstr_fd(a, 1);
}
