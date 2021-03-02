/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_s.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 18:50:57 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/02 11:41:14 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_data_s(struct fields *fp, t_data *data, const char *sval)
{
	data->a = ft_strdup(sval);
	if (!data->a)
	{
		fp->count = -1;
		return ;
	}
	data->a_len = strlen(data->a);
}

void	precision_s(struct fields *fp, t_data *data)
{
	if (fp->precision >= 0 && fp->precision < (int)data->a_len)
	{
		data->a[fp->precision] = '\0';
		data->a_len = strlen(data->a);
	}
}

void	width_s(struct fields *fp, t_data *data)
{
	if (fp->width > (int)data->a_len)
	{
		data->b = zalloc(fp->width + data->a_len + 1, sizeof(*(data->b)),
				fp->padding_char);
		if (!data->b)
		{
			fp->count = -1;
			return ;
		}
		data->b_dup = data->b;
		if (fp->is_minus)
			memcpy(data->b_dup, data->a, data->a_len);
		else
			memcpy(data->b_dup + (fp->width - data->a_len), data->a,
					data->a_len);
		data->b[fp->width] = '\0';
		free(data->a);
		data->a = data->b;
		data->a_len = strlen(data->a);
	}
}

void	format_s(struct fields *fp, const char *sval)
{
	t_data	data;

	get_data_s(fp, &data, sval);
	if (fp->count == -1)
		return ;
	precision_s(fp, &data);
	width_s(fp, &data);
	if (fp->count == -1)
		return ;
	ft_putstr_fd(data.a, 1);
	fp->count = fp->count + data.a_len;
	free(data.a);
}
