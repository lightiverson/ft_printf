/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_p.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 18:51:38 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/06 10:42:47 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Prepends "0x" to data->a.

1.	Sets data->b to equal a malloced string the size
	of "0x" and data->a. And joins the two strings.
2.	Free's data->a to prevent unfreed malloced memory.
3.	Sets data->a to data->b.
4.	Updates data->a_dup, data->a_len and data->a_digits
	because there's a new data->a.

t_fields *fields -- pointer to struct that contains information
	on fields
t_data *data -- pointer to struct that contains information on
	the variadic argument to be formatted and printed
*/

void	prepend_0x(t_fields *fields, t_data *data)
{
	if (*data->a == '0' && fields->precision != -1)
		*data->a = '\0';
	data->b = ft_strjoin("0x", data->a);
	if (!data->b)
	{
		fields->count = -1;
		return ;
	}
	free(data->a);
	data->a = data->b;
	data->a_dup = data->a;
	data->a_len = ft_strlen(data->a);
	data->a_digits = get_alnum(data->a);
}

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

void	get_data_p(t_fields *fields, t_data *data, unsigned long pval)
{
	data->a = uitoa_hex(pval);
	if (!data->a)
	{
		fields->count = -1;
		return ;
	}
	data->a_dup = data->a;
	data->a_len = ft_strlen(data->a);
	data->a_digits = get_alnum(data->a);
}

/* Handles %p conversion specifier.

Converts unsigned long int to formatted string. And
	outputs it to the standard output.

t_fields *fields -- pointer to struct that contains information
	on fields
unsigned long pval -- variadic argument
*/

void	format_p(t_fields *fields, unsigned long pval)
{
	t_data	data;

	get_data_p(fields, &data, pval);
	if (fields->count == -1)
		return ;
	prepend_0x(fields, &data);
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
