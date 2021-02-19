/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_u.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:04:32 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/19 21:47:16 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_data_u(struct fields *fp, t_data *data, unsigned int uval)
{
	data->a = uitoa(uval);
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

void	format_u(struct fields *fp, unsigned int uval)
{
	t_data data;

	get_data_u(fp, &data, uval);
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
