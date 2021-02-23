/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   precision_width_diux.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 12:56:31 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/23 12:57:42 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	diux_nega_helper(t_data *data)
{
	*data->b_dup++ = '-';
	data->a_dup++;
}

void	precision_diux(struct fields *fp, t_data *data)
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
			diux_nega_helper(data);
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

void	width_diux(t_data *data, struct fields *fp)
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
				diux_nega_helper(data);
			memcpy(data->b_dup + (fp->width - data->a_len),
				data->a_dup, strlen(data->a_dup));
		}
		data->b[fp->width] = '\0';
		free(data->a);
		data->a = data->b;
		data->a_len = strlen(data->a);
	}
}
