/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   precision_width_diuxp.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 12:56:31 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/06 12:24:44 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Helps the precision_diuxp() and width_diuxp()
	functions to handle negative values.

Works by setting the first character of data->b_dup
	to '-' sign. And setting data->a_dup one character
	forward to ignore the minus sign before continuing
	with the calling function.

t_data *data -- pointer to struct that contains information on
	the variadic argument to be formatted and printed
*/

static void	diuxp_nega_helper(t_data *data)
{
	*data->b_dup++ = '-';
	data->a_dup++;
}

/* Handles the precision for %d, %i, %u, %x, and %p specifiers.

1.	Check if the precision is smaller than the number of
	characters in the converted(!) value.
2.	Malloc data->b with enough memory to hold precision,
	data->a_len and terminating null character. Also fill data->b
	width '0'.
3.	Use data-b_dup to move around the data->b string without losing
	original position.
4.	If the first character of the converted(!) value is '-':
		I.	Set data->b_dup's first character to '-'.
			and Increment data->b_dup by one.
		II.	Increment data->a_dup by one.
		This will turn a string representation of a negative number
		into a string representation of a positive number. And set
		the '-' sign in the correct place in the converted string.
		After which the regular flow can be followed.
	Copy the converted value data->a_dup to the
	(data->b_dup + (fields->precision - data->a_digits))th position in the
	string of data->b_dup.
5.	Set a null terminating character at the fields->precision'th index
	of data->b_dup.
6.	Set data->a to data->b.
7.	Set data->a_dup to the new data->a.
8.	Updates data->a_len because data->a points to a new string.
9.	Handle one off edge case.

t_fields *fields -- pointer to struct that contains information
	on fields
t_data *data -- pointer to struct that contains information on
	the variadic argument to be formatted and printed
*/

void	precision_diuxp(t_fields *fields, t_data *data)
{
	if (fields->precision >= 0 && data->a_digits < fields->precision)
	{
		data->b = zalloc(fields->precision + data->a_len + 1,
				sizeof(*(data->b)), '0');
		if (!data->b)
		{
			fields->count = -1;
			return ;
		}
		data->b_dup = data->b;
		if (*data->a == '-')
			diuxp_nega_helper(data);
		ft_memcpy(data->b_dup + (fields->precision - data->a_digits), data->a_dup,
				ft_strlen(data->a_dup));
		data->b_dup[fields->precision] = '\0';
		free(data->a);
		data->a = data->b;
		data->a_dup = data->a;
	}
	else if (fields->precision == 0 && (*data->a == '0' && data->a[1] == '\0'))
		data->a[0] = '\0';
	data->a_len = ft_strlen(data->a);
}

/* Handles the width for %d, %i, %u, %x, and %p specifiers.

1.	Check if the converted(!) value has fewer characters than the
	field width.
2.	Malloc data->b with enough memory to hold width, data->a_len and
	terminating null character. Also fill data->b with
	fields->padding_char.
3.	Use data-b_dup to move around the data->b string without losing
	original position.
4.	If data->minus is true, copies the converted value data->a to
	the beginning of data->b_dup.

	If data->minus is false, check for case where the converted(!)
	value is negative and the padding_char == '0'. If so:
		I.	Set data->b_dup's first character to '-'.
			and Increment data->b_dup by one.
		II.	Increment data->a_dup by one.
		This will turn a string representation of a negative number
		into a string representation of a positive number. And set
		the '-' sign in the correct place in the converted string.
		After which the regular flow can be followed.
	Copy the converted value data->a_dup to the
	(data->b_dup + (fields->width - data->a_len))th position in the
	string of data->b_dup.
5.	Null terminate data->b on index fields->width.
6.	Free data->a to prevent unfreed malloced memory.
7.	Set data->a to data->b.
8.	Updates data->a_len because data->a points to a new string.

t_fields *fields -- pointer to struct that contains information
	on fields
t_data *data -- pointer to struct that contains information on
	the variadic argument to be formatted and printed
*/

void	width_diuxp(t_data *data, t_fields *fields)
{
	if ((int)data->a_len < fields->width)
	{
		data->b = zalloc(fields->width + data->a_len + 1,
				sizeof(*(data->b)), fields->padding_char);
		if (!data->b)
		{
			fields->count = -1;
			return ;
		}
		data->b_dup = data->b;
		if (fields->is_minus)
			ft_memcpy(data->b_dup, data->a, data->a_len);
		else
		{
			if (*data->a == '-' && fields->padding_char == '0')
				diuxp_nega_helper(data);
			ft_memcpy(data->b_dup + (fields->width - data->a_len),
				data->a_dup, ft_strlen(data->a_dup));
		}
		data->b[fields->width] = '\0';
		free(data->a);
		data->a = data->b;
		data->a_len = ft_strlen(data->a);
	}
}
