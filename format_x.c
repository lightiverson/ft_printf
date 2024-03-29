/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_x.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 20:50:23 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/06 10:51:44 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Gets data needed to format string according to fields.

1.	Sets data->a to a string representation of the variadic argument.
2.	Sets data->a_dup to data->a to move around the string while data->a
	remains at the original position.
3.	Sets data->a_len to be the length of data->a.
4.	Sets data->a_digits to be the number of digits in data->a, in case
	there's a minus sign.

With the above mentioned data you can take care of all formating
requirements for this project.

t_fields *fields -- pointer to struct that contains information
	on fields
t_data *data -- pointer to struct that contains information on
	the variadic argument to be formatted and printed
unsigned int xval -- variadic argument
*/

void	get_data_x(t_fields *fields, t_data *data, unsigned int xval)
{
	data->a = uitoa_hex(xval);
	if (!data->a)
	{
		fields->count = -1;
		return ;
	}
	data->a_dup = data->a;
	data->a_len = ft_strlen(data->a);
	data->a_digits = get_alnum(data->a);
}

/* Handles %x and %X conversion specifiers.

Converts unsigned int to formatted string. And
	outputs it to the standard output.

t_fields *fields -- pointer to struct that contains information
	on fields
unsigned int xval -- variadic argument
*/

void	format_x(t_fields *fields, unsigned int xval)
{
	t_data	data;

	get_data_x(fields, &data, xval);
	if (fields->count == -1)
		return ;
	precision_diuxp(fields, &data);
	if (fields->count == -1)
		return ;
	width_diuxp(&data, fields);
	if (fields->count == -1)
		return ;
	if (fields->conv_char == 'X')
		data.a = str_toupper(data.a);
	ft_putstr_fd(data.a, 1);
	fields->count = fields->count + data.a_len;
	free(data.a);
}
