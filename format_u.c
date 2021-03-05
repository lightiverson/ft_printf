/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_u.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:04:32 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/05 14:02:48 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_data_u(t_fields *fields, t_data *data, unsigned int uval)
{
	data->a = uitoa(uval);
	if (!data->a)
	{
		fields->count = -1;
		return ;
	}
	data->a_dup = data->a;
	data->a_len = ft_strlen(data->a);
	data->a_digits = get_alnum(data->a);
}

void	format_u(t_fields *fields, unsigned int uval)
{
	t_data	data;

	get_data_u(fields, &data, uval);
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
