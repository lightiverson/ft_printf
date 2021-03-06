/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_di.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 14:51:41 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/06 10:45:25 by kawish        ########   odam.nl         */
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
int dval -- variadic argument
*/

void	get_data_di(t_fields *fields, t_data *data, int dval)
{
	data->a = ft_itoa(dval);
	if (!data->a)
	{
		fields->count = -1;
		return ;
	}
	data->a_dup = data->a;
	data->a_len = ft_strlen(data->a);
	data->a_digits = get_alnum(data->a);
}

/* Handles %d and %i conversion specifiers.

Converts integers to formatted string. And outputs it
to the standard output.

t_fields *fields -- pointer to struct that contains information
	on fields
int dval -- variadic argument
*/

void	format_di(t_fields *fields, int dval)
{
	t_data	data;

	get_data_di(fields, &data, dval);
	if (fields->count == -1)
		return ;
	precision_diuxp(fields, &data);
	if (fields->count == -1)
		return ;
	width_diuxp(&data, fields);
	if (fields->count == -1)
		return ;
	ft_putstr_fd(data.a, 1);
	fields->count = fields->count + data.a_len;
	free(data.a);
}
