/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   uitoa.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/22 12:02:05 by kgajadie      #+#    #+#                 */
/*   Updated: 2021/02/23 11:19:57 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	unsigned int	ft_int2pwr(int x, int n)
{
	int				i;
	unsigned int	result;

	i = 0;
	result = 1;
	while (i < n)
	{
		result *= x;
		i++;
	}
	return (result);
}

static	size_t			ft_intlen(unsigned int n)
{
	size_t len;

	len = 1;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 9)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char					*uitoa(unsigned int n)
{
	unsigned int	i;
	size_t			len;
	char			*str;

	i = 0;
	len = ft_intlen(n);
	str = ft_calloc(len + 1, sizeof(*str));
	if (!str)
		return (0);
	len = len - i;
	while (len > 0)
	{
		str[i] = ((n / ft_int2pwr(10, len - 1)) % 10) + '0';
		i++;
		len--;
	}
	return (str);
}
