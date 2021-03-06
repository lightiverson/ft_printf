/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   uitoa_hex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 11:36:09 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/06 12:45:59 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_no_of_digits(unsigned long n)
{
	int	i;

	i = 1;
	while (n > 15)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static unsigned long	ui_pow(int base, int exponent)
{
	int				i;
	unsigned long	r;

	i = 0;
	r = 1;
	while (i < exponent)
	{
		r = r * base;
		i++;
	}
	return (r);
}

static unsigned long	get_largest_exponent(unsigned long n)
{
	unsigned long	i;
	unsigned long	y;

	i = 1;
	y = n;
	while (n / ui_pow(16, i) != 0)
		i++;
	i = i - 1;
	return (i);
}

/* Variation on libft's itoa.

Edited to work with unsigned long n. And more
importantly convert base 10 number to base 16.

Uses mathematical flow of:
1.	x equals the largest exponent of 16 that fits into n.
2.	y equals n divided by x. y is the first base 16 digit
	starting from left to right. 
3.	n equals the remainder from n divided by x.
4.	decrease the exponential by 1.

unsigned long n -- number to convert
*/

char	*uitoa_hex(unsigned long n)
{
	int				i;
	unsigned long	y;
	int				no_of_digits;
	unsigned long	largest_exponent;
	char			*str;

	i = 0;
	no_of_digits = get_no_of_digits(n);
	largest_exponent = get_largest_exponent(n);
	str = ft_calloc(no_of_digits + 1, sizeof(*str));
	if (!str)
		return (0);
	while (i < no_of_digits)
	{
		y = n / ui_pow(16, largest_exponent);
		n = n % ui_pow(16, largest_exponent);
		largest_exponent = largest_exponent - 1;
		if (y < 10)
			str[i] = y + '0';
		else
			str[i] = y - 10 + 'a';
		i++;
	}
	return (str);
}
