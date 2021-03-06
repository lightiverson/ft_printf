/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_c.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/09 14:39:10 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/06 10:10:10 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Handles %c conversion specifier.

Prints char to standard output along with conversions
due to formatting.

t_fields *fields -- pointer to struct that contains information
	on fields
unsigned char cval -- variadic argument
*/

void	format_c(t_fields *fields, unsigned char cval)
{
	int	i;

	i = 1;
	if (!fields->is_minus)
	{
		while (i < fields->width)
		{
			write(1, &(fields->padding_char), 1);
			i++;
		}
	}
	write(1, &cval, 1);
	if (fields->is_minus)
	{
		while (i < fields->width)
		{
			write(1, &(fields->padding_char), 1);
			i++;
		}
	}
	fields->count = fields->count + i;
}
