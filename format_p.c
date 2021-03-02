/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_p.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 18:51:38 by kawish        #+#    #+#                 */
/*   Updated: 2021/03/02 13:04:51 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	prepend_0x(struct fields *fp, t_data *data)
{
	if (*data->a == '0' && fp->precision != -1)
		*data->a = '\0';
	data->b = ft_strjoin("0x", data->a);
	if (!data->b)
	{
		fp->count = -1;
		return ;
	}
	free(data->a);
	data->a = data->b;
	data->a_dup = data->a;
	data->a_len = strlen(data->a);
}

void	get_data_p(struct fields *fp, t_data *data, unsigned long pval)
{
	data->a = uitoa_hex(pval);
	if (!data->a)
	{
		fp->count = -1;
		return ;
	}
	data->a_dup = data->a;
	data->a_len = strlen(data->a);
	data->a_digits = get_alnum(data->a);
}

void	format_p(struct fields *fp, unsigned long pval)
{
	t_data	data;

	get_data_p(fp, &data, pval);
	if (fp->count == -1)
		return ;
	prepend_0x(fp, &data);
	if (fp->count == -1)
		return ;
	precision_diuxp(fp, &data);
	if (fp->count == -1)
		return ;
	width_diuxp(&data, fp);
	if (fp->count == -1)
		return ;
	ft_putstr_fd(data.a, 1);
	fp->count = fp->count + data.a_len;
	free(data.a);
}
