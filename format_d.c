/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 14:51:41 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/26 21:36:59 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_data_d(struct fields *fp, t_data *data, int dval)
{
	data->a = ft_itoa(dval);
	if (!data->a)
	{
		fp->count = -1;
		return ;
	}
	data->a_dup = data->a;
	data->a_len = strlen(data->a);
	data->a_digits = get_alnum(data->a);
}

void	format_d(struct fields *fp, int dval)
{
	t_data data;

	get_data_d(fp, &data, dval);
	if (fp->count == -1)
		return ;
	precision_diux(fp, &data);
	if (fp->count == -1)
		return ;
	width_diux(&data, fp);
	if (fp->count == -1)
		return ;
	ft_putstr_fd(data.a, 1);
	fp->count = data.a_len;
	free(data.a);
}
