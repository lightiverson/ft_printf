/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_u.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:04:32 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/26 21:38:32 by kawish        ########   odam.nl         */
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
	data->a_digits = get_alnum(data->a);
}

void	format_u(struct fields *fp, unsigned int uval)
{
	t_data data;

	get_data_u(fp, &data, uval);
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
