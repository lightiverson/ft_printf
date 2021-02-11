/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_u.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:04:32 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/11 16:22:19 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*precision_u(struct fields *fp, char *a, int a_len)
{
	char r[fp->precision + a_len + 1];
	char *p_r;

	p_r = r;
	memset(r, '0', sizeof(r));
	memcpy(p_r + (fp->precision - a_len), a, strlen(a));
	r[fp->precision] = '\0';
	free(a);
	return (ft_strdup(r));
}

char	*width_u(struct fields *fp, char *a, int a_len)
{
	char r[fp->width + a_len + 1];
	char *p_r;

	p_r = r;
	memset(p_r, fp->padding_char, sizeof(r));
	if (fp->is_minus)
		memcpy(p_r, a, strlen(a));
	else
		memcpy(p_r + (fp->width - a_len), a, strlen(a));
	r[fp->width] = '\0';
	free(a);
	return (ft_strdup(r));
}

void	format_u(struct fields *fp, unsigned int uval)
{
	char	*a;
	int		a_len;

	a = ft_itoa(uval);
	if (!a)
	{
		fp->count = -1;
		return ;
	}
	a_len = strlen(a);
	if (fp->precision >= 0 && fp->precision > a_len)
	{
		a = precision_u(fp, a, a_len);
		a_len = strlen(a);
	}
	else if (fp->precision == 0 && uval == 0)
	{
		memset(a, '\0', strlen(a) + 1);
		a_len = strlen(a);
	}
	if (fp->width > a_len)
		a = width_u(fp, a, a_len);
	fp->count = fp->count + strlen(a);
	ft_putstr_fd(a, 1);
	free(a);
	return ;
}
