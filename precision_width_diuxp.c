/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   precision_width_diuxp.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 12:56:31 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/04 10:50:16 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** zalloc: Custom function that mallocs,
** checks if malloc has worked,
** and fills the malloced array with CHAR C.
*/

static void	diuxp_nega_helper(t_data *data)
{
	*data->b_dup++ = '-';
	data->a_dup++;
}

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
		memcpy(data->b_dup + (fields->precision - data->a_digits), data->a_dup,
				strlen(data->a_dup));
		data->b_dup[fields->precision] = '\0';
		free(data->a);
		data->a = data->b;
		data->a_dup = data->a;
	}
	else if (fields->precision == 0 && (*data->a == '0' && data->a[1] == '\0'))
		data->a[0] = '\0';
	data->a_len = strlen(data->a);
}

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
			memcpy(data->b_dup, data->a, data->a_len);
		else
		{
			if (*data->a == '-' && fields->padding_char == '0')
				diuxp_nega_helper(data);
			memcpy(data->b_dup + (fields->width - data->a_len),
				data->a_dup, strlen(data->a_dup));
		}
		data->b[fields->width] = '\0';
		free(data->a);
		data->a = data->b;
		data->a_len = strlen(data->a);
	}
}
