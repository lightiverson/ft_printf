/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   uitoa_hex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 11:36:09 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/04 12:30:11 by kawish        ########   odam.nl         */
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

/* 
2 regels te veel
ga er doorheen met debugger
kijk of er een andere conditional gebruikt kan woorden dan i
*/

char	*uitoa_hex(unsigned long n)
{
	int				i;
	unsigned long	y;
	int				no_of_digits;
	unsigned long	largest_exponent;
	char			*str;
	char			c;

	i = 0;
	y = 0;
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
			c = y + '0';
		else
			c = y - 10 + 'a';
		str[i] = c;
		i++;
	}
	return (str);
}
