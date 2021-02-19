/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 14:51:41 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/19 15:24:31 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_data(struct fields *fp, t_data *data, int dval)
{
	data->a = ft_itoa(dval);
	if (!data->a)
	{
		fp->count = -1;
		return ;
	}
	data->a_dup = data->a;
	data->a_len = strlen(data->a);
	data->a_digits = get_digits(data->a);
	return ;
}

void	precision_d_nega(t_data *data)
{
	*data->b_dup++ = '-';
	data->a_dup++;
}

void	precision_d(struct fields *fp, t_data *data)
{
	if (fp->precision >= 0 && data->a_digits < fp->precision)
	{
		data->b = zalloc(fp->precision + data->a_len + 1,
			sizeof(*(data->b)), '0');
		if (!data->b)
		{
			fp->count = -1;
			return ;
		}
		data->b_dup = data->b;
		if (*data->a == '-')
			precision_d_nega(data);
		memcpy(data->b_dup + (fp->precision - data->a_digits),
			data->a_dup, strlen(data->b_dup));
		data->b_dup[fp->precision] = '\0';
		free(data->a);
		data->a = data->b;
		data->a_dup = data->a;
	}
	else if (fp->precision == 0 && *data->a == '0')
		data->a[0] = '\0';
	data->a_len = strlen(data->a);
}

void	width_d(t_data *data, struct fields *fp)
{
	if ((int)data->a_len < fp->width)
	{
		data->b = zalloc(fp->width + data->a_len + 1,
			sizeof(*(data->b)), fp->padding_char);
		if (!data->b)
		{
			fp->count = -1;
			return ;
		}
		data->b_dup = data->b;
		if (fp->is_minus)
			memcpy(data->b_dup, data->a, data->a_len);
		else
		{
			if (*data->a == '-' && fp->padding_char == '0')
				precision_d_nega(data);
			memcpy(data->b_dup + (fp->width - data->a_len),
				data->a_dup, strlen(data->a_dup));
		}
		data->b[fp->width] = '\0';
		free(data->a);
		data->a = data->b;
		data->a_len = strlen(data->a);
	}
}

void	format_d(struct fields *fp, int dval)
{
	t_data data;

	get_data(fp, &data, dval);
	if (fp->count == -1)
		return ;
	precision_d(fp, &data);
	if (fp->count == -1)
		return ;
	width_d(&data, fp);
	if (fp->count == -1)
		return ;
	ft_putstr_fd(data.a, 1);
	free(data.a);
	return ;
}
