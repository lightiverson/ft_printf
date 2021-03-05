/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_x.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 20:50:23 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/05 14:03:14 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
