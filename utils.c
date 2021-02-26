/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 14:55:01 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/26 19:33:25 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int		get_alnum(char *s)
{
	int i;

	i = 0;
	while (*s)
	{
		if (isalnum(*s))
			i++;
		s++;
	}
	return (i);
}

char	*str_toupper(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = toupper(str[i]);
		i++;
	}
	return (str);
}

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
