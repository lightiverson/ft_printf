/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_p.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 18:51:38 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/04 10:49:11 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	data->a_len = strlen(data->a);
}

void	get_data_p(t_fields *fields, t_data *data, unsigned long pval)
{
	data->a = uitoa_hex(pval);
	if (!data->a)
	{
		fields->count = -1;
		return ;
	}
	data->a_dup = data->a;
	data->a_len = strlen(data->a);
	data->a_digits = get_alnum(data->a);
}

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
