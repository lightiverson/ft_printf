/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_s.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 18:50:57 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/05 15:15:44 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

void	precision_s(t_fields *fields, t_data *data)
{
	if (fields->precision >= 0 && fields->precision < (int)data->a_len)
	{
		data->a[fields->precision] = '\0';
		data->a_len = ft_strlen(data->a);
	}
}

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
