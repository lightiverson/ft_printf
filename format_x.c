/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_x.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/20 20:50:23 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/26 19:02:28 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_data_x(struct fields *fp, t_data *data, unsigned int xval)
{
	data->a = uitoa_hex(xval);
	if (!data->a)
	{
		fp->count = -1;
		return ;
	}
	data->a_dup = data->a;
	data->a_len = strlen(data->a);
	data->a_digits = get_alnum(data->a);
}

void	format_x(struct fields *fp, unsigned int xval)
{
	t_data data;

	get_data_x(fp, &data, xval);
	if (fp->count == -1)
		return ;
	precision_diux(fp, &data);
	if (fp->count == -1)
		return ;
	width_diux(&data, fp);
	if (fp->count == -1)
		return ;
	if (fp->conv_char == 'X')
		data.a = str_toupper(data.a);
	ft_putstr_fd(data.a, 1);
	free(data.a);
}
