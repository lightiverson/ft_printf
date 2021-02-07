/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 14:51:41 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/07 12:09:34 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			count_chars(int n)
{
	int c;

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
	int c;

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

char*		precision_d(struct fields *fp, int dval, char *a, int digits_a, int chars_a)
{
	char ret[fp->precision + chars_a + 1];
	char *p_ret;

	p_ret = ret;
	memset(ret, '0', sizeof(ret));
	
	if (dval < 0)
	{
		*p_ret++ = '-';
		a++;
	}

	strlcpy(p_ret+(fp->precision - digits_a), a, strlen(p_ret) + 1);

	return(ft_strdup(ret));
}

char*		width_d(struct fields *fp, int dval, char *a, int chars_a)
{
	// fp->width = 7
	// chars_a = 2
	// a = "33"
	char ret[fp->width + chars_a + 1];
	char *p_ret;
	int i;

	p_ret = ret;
	i = 0;

	memset(ret, fp->padding_char, sizeof(ret));

	if (fp->is_minus)
	{
		/* 33 moet links komen */
		// ret = "3.300.000.000"
		memcpy(ret, a, strlen(a));
	}
	else
	{
		/* 33 moet rechts komen */
		// ret = "0.000.033.000"
		// alleen bij right aligned kan je met nullen padden

		// if (dval < 0)
		// {
		// 	ret[i] = '-';
		// 	i++;
		// 	memcpy( &(ret[fp->width - (chars_a - i)]), &(a[i]), strlen(&(a[i])) );
		// }
		// else
		// {
		// 	memcpy(&(ret[fp->width - chars_a]), a, strlen(a));
		// }

		if (dval < 0 && fp->padding_char == '0')
		{
			*p_ret++ = '-';
			a++;
		}
		memcpy(p_ret+(fp->width - chars_a), a, strlen(a));
	}

	ret[fp->width] = '\0';
	
	return(ft_strdup(ret));
}

void		format_d(struct fields *fp, int dval)
{
	// Eigenlijk heb je ze alle drie nodig:
	// het aantal digits
	// het aantal characters
	// de string of dval

	char			*a;
	int				digits_a;
	int				chars_a;

	a = ft_itoa(dval);
	if (!a)
		return;
	
	// if (dval == 0)
	// 	memset(a, '\0', strlen(a) + 1);

	digits_a = count_digits(dval);
	// printf("digits_a = %d\n", digits_a);

	chars_a = count_chars(dval);
	// printf("chars_a = %d\n", chars_a);

	if (fp->precision >= 0 && digits_a < fp->precision)
	{
		// a = precision_d(fp, a, digits_a);
		a = precision_d(fp, dval, a, digits_a, chars_a);
		chars_a = (int)strlen(a);
	}
	else if (fp->precision == 0 && dval == 0)
	{
		memset(a, '\0', strlen(a) + 1);
		chars_a = (int)strlen(a);
	}

	// width
	if (chars_a < fp->width) // 3 < 5
	{
		// a = width_d(chars_a, fp, dval, digits_a, a);
		a = width_d(fp, dval, a, chars_a);
	}

	ft_putstr_fd(a, 1);
}