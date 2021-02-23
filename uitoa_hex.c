/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   uitoa_hex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 11:36:09 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/23 12:02:45 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
static	int		ft_int2pwr_twee(int x, int n)
{
	int i;
	int result;

	i = 0;
	result = 1;
	while (i < n)
	{
		result *= x;
		i++;
	}
	return (result);
}

int				get_largest_power(unsigned int n)
{
	int				i;
	unsigned int	n_dup;

	i = 0;
	n_dup = n;
	while (n_dup != 0)
	{
		n_dup = n / ft_int2pwr_twee(16, i);
		i++;
	}
	i = i - 2;
	return (i);
}

char			*uitoa_hex(unsigned int n)
{
	unsigned int	i;
	int				largest_power;
	char			*str;
	unsigned int	r;
	char			c;

	i = 0;
	largest_power = get_largest_power(n);
	str = ft_calloc(largest_power + 1, sizeof(*str));
	if (!str)
		return (0);
	while (largest_power >= 0)
	{
		r = n / ft_int2pwr_twee(16, largest_power);
		if (r < 10)
			c = r + '0';
		else
			c = r - 10 + 'a';
		str[i] = c;
		i++;
		n = n - (r * ft_int2pwr_twee(16, largest_power));
		largest_power = largest_power - 1;
	}
	return (str);
}
*/

static int				len_nb(unsigned long n)
{
	int		i;
	long	nb;

	i = 0;
	nb = n;
	while (nb != 0)
	{
		nb = nb / 16;
		i++;
	}
	if (i == 0)
		return (1);
	else
		return (i);
}

static unsigned long	power(int base, int pow)
{
	unsigned long	result;

	result = 1;
	while (pow != 0)
	{
		result = result * base;
		pow--;
	}
	return (result);
}

char					*uitoa_hex(unsigned long n)
{
	int				i;
	int				len;
	unsigned long	result;
	char			*n_str;

	i = 0;
	len = len_nb(n);
	n_str = (char*)malloc(sizeof(char) * (len + 1));
	if (n_str == NULL)
		return (NULL);
	while (i < len)
	{
		result = n / power(16, len - 1 - i);
		result = result % 16;
		if (result < 10)
			*(n_str + i) = result + '0';
		else
			*(n_str + i) = result - 10 + 'a';
		i++;
	}
	*(n_str + i) = '\0';
	return (n_str);
}