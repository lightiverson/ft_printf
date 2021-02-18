/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 14:51:41 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/18 11:03:44 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				count_chars(int n)
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

int				count_digits(int n)
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

static void		get_a(struct fields *fp, int dval, char **a, int *chars_a)
{
	*a = ft_itoa(dval);
	if (!*a)
	{
		fp->count = -1;
		return ;
	}
	*chars_a = strlen(*a);
}

void			precision_d(struct fields *fp, int dval, char **a, int *chars_a)
{
	int		digits_a;
	char	*r;
	char	*r_dup;
	char	*a_dup;

	a_dup = *a;
	digits_a = count_digits(dval);
	if (fp->precision >= 0 && digits_a < fp->precision)
	{
		r = zalloc(fp->precision + *chars_a + 1, sizeof(*r), '0');
		if (!r)
		{
			fp->count = -1;
			return ;
		}
		r_dup = r;
		if (dval < 0)
		{
			*r_dup++ = '-';
			a_dup++;
		}
		strlcpy(r_dup + (fp->precision - digits_a), a_dup, strlen(r_dup) + 1);
		free(*a);
		*a = r;
	}
	else if (fp->precision == 0 && dval == 0)
		memset(*a, '\0', strlen(*a) + 1);
	*chars_a = strlen(*a);
}

void			width_d(struct fields *fp, int dval, char **a, int *chars_a)
{
	char *r;
	char *r_dup;
	char *a_dup;

	a_dup = *a;
	if (*chars_a < fp->width)
	{
		r = zalloc(fp->width + *chars_a + 1, sizeof(*r), fp->padding_char);
		if (!r)
		{
			fp->count = -1;
			return ;
		}
		r_dup = r;
		if (fp->is_minus)
			memcpy(r_dup, *a, strlen(*a));
		else
		{
			if (dval < 0 && fp->padding_char == '0')
			{
				*r_dup++ = '-';
				a_dup++;
			}
			memcpy(r_dup + (fp->width - *chars_a), a_dup, strlen(*a));
		}
		r[fp->width] = '\0';
		free(*a);
		*a = r;
		*chars_a = strlen(*a);
	}
}

void			format_d(struct fields *fp, int dval)
{
	char			*a;
	int				digits_a;
	int				chars_a;

	chars_a = 0;
	get_a(fp, dval, &a, &chars_a);
	if (fp->count == -1)
		return ;
	digits_a = count_digits(dval);
	precision_d(fp, dval, &a, &chars_a);
	if (fp->count == -1)
		return ;
	width_d(fp, dval, &a, &chars_a);
	if (fp->count == -1)
		return ;
	fp->count = fp->count + chars_a;
	ft_putstr_fd(a, 1);
	free(a);
	return ;
}
