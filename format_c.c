/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_c.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/09 14:39:10 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/26 10:27:54 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	format_c(struct fields *fp, char cval)
{
	int i;

	i = 1;
	if (!fp->is_minus)
	{
		while (i < fp->width)
		{
			write(1, &(fp->padding_char), 1);
			i++;
		}
	}
	write(1, &cval, 1);
	if (fp->is_minus)
	{
		while (i < fp->width)
		{
			write(1, &(fp->padding_char), 1);
			i++;
		}
	}
	fp->count = fp->count + i;
}
