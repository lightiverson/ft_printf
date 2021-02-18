/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 14:55:01 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/18 22:53:42 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		int_len(int n)
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

/*
** is_nonzerodigit: checkt of c een digit is, behalve 0, inclusief - teken
*/

int		is_nonzerodigit(int c)
{
	if ((c >= '1' && c <= '9') || (c == '-'))
		return (1);
	else
		return (0);
}

/*
** zalloc: Custom function that mallocs,
** checks if malloc has worked,
** and fills the malloced array with CHAR C.
*/

void	*zalloc(size_t count, size_t size, char c)
{
	void	*a;

	if ((count == 0) || (size == 0))
	{
		count = 1;
		size = 1;
	}
	a = malloc(count * size);
	if (a)
		ft_memset(a, c, count * size);
	return (a);
}

int		count_digits(int n)
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

int		count_chars(int n)
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

int		get_digits(char *s)
{
	int i;

	i = 0;
	while (*s)
	{
		if (isdigit(*s))
			i++;
		s++;
	}
	return (i);
}