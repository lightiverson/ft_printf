/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_s.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 18:50:57 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/06 11:32:14 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Gets data needed to format string according to fields.

1.	Sets data->a to a string representation of the variadic argument.
2.	Sets data->a_len to be the length of data->a.

t_fields *fields -- pointer to struct that contains information
	on fields
t_data *data -- pointer to struct that contains information on
	the variadic argument to be formatted and printed
const char *sval -- variadic argument
*/

void	get_data_s(t_fields *fields, t_data *data, const char *sval)
{
	data->a = ft_strdup(sval);
	if (!data->a)
	{
		fields->count = -1;
		return ;
	}
	data->a_len = ft_strlen(data->a);
}

/* Handles the precision for %s conversion specifier.

Is different from precision_diuxp() because for %s precision
	gives the maximum number of characters to be printed.

1.	Check if the precision is smaller than the number of
	characters in the converted(!) value.
2.	Set a null terminating character at the fields->precision'th
	index of the converted(!) value.

t_fields *fields -- pointer to struct that contains information
	on fields
t_data *data -- pointer to struct that contains information on
	the variadic argument to be formatted and printed
*/

void	precision_s(t_fields *fields, t_data *data)
{
	if (fields->precision >= 0 && fields->precision < (int)data->a_len)
	{
		data->a[fields->precision] = '\0';
		data->a_len = ft_strlen(data->a);
	}
}

/* Handles the width for %s conversion specifier.

Is different from width_diuxp() because the '-' sign
should be handeled differently for %s than for % -diuxp.

1.	Check if the converted(!) value has fewer characters than the
	field width.
2.	Malloc data->b with enough memory to hold width, data->a_len and
	terminating null character. Also fill data->b with padding
	character.
3.	Use data-b_dup to move around the data->b string without losing
	original position.
4.	If data->minus is true, copy the converted value data->a to
	the beginning of data->b_dup.
	If data->minus is false, copy the converted value data->a to
	the (data->b_dup + (fields->width - data->a_len))th position in the
	string of data->b.
5.	Null terminate data->b on index fields->width.
6.	Free data->a to prevent unfreed malloced memory.
7.	Set data->a to data->b.
8.	Updates data->a_len because data->a points to a new string.

t_fields *fields -- pointer to struct that contains information
	on fields
t_data *data -- pointer to struct that contains information on
	the variadic argument to be formatted and printed
*/

void	width_s(t_fields *fields, t_data *data)
{
	if (fields->width > (int)data->a_len)
	{
		data->b = zalloc(fields->width + data->a_len + 1, sizeof(*(data->b)),
				fields->padding_char);
		if (!data->b)
		{
			fields->count = -1;
			return ;
		}
		data->b_dup = data->b;
		if (fields->is_minus)
			ft_memcpy(data->b_dup, data->a, data->a_len);
		else
			ft_memcpy(data->b_dup + (fields->width - data->a_len), data->a,
				data->a_len);
		data->b[fields->width] = '\0';
		free(data->a);
		data->a = data->b;
		data->a_len = ft_strlen(data->a);
	}
}

/* Handles %s conversion specifier.

Converts const char to formatted string. And outputs
	it to the standard output.

t_fields *fields -- pointer to struct that contains information
	on fields
const char *sval -- variadic argument
*/

void	format_s(t_fields *fields, const char *sval)
{
	t_data	data;

	get_data_s(fields, &data, sval);
	if (fields->count == -1)
		return ;
	precision_s(fields, &data);
	width_s(fields, &data);
	if (fields->count == -1)
		return ;
	ft_putstr_fd(data.a, 1);
	fields->count = fields->count + data.a_len;
	free(data.a);
}
