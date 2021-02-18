/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_u.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:04:32 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/18 11:02:13 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_a(struct fields *fp, unsigned int uval, char **a, int *a_len)
{
	*a = ft_itoa(uval);
	if (!*a)
	{
		fp->count = -1;
		return ;
	}
	*a_len = strlen(*a);
}

void		precision_u(struct fields *fp, unsigned int uval,
	char **a, int *a_len)
{
	char *r;
	char *r_dup;

	if (fp->precision >= 0 && fp->precision > *a_len)
	{
		r = zalloc(fp->precision + *a_len + 1, sizeof(*r), '0');
		if (!r)
		{
			fp->count = -1;
			return ;
		}
		r_dup = r;
		memcpy(r_dup + (fp->precision - *a_len), *a, *a_len);
		r[fp->precision] = '\0';
		free(*a);
		*a = r;
	}
	else if (fp->precision == 0 && uval == 0)
		memset(*a, '\0', *a_len + 1);
	*a_len = strlen(*a);
}

void		width_u(struct fields *fp, char **a, int *a_len)
{
	char *r;
	char *r_dup;

	if (fp->width > *a_len)
	{
		r = zalloc(fp->width + *a_len + 1, sizeof(char), fp->padding_char);
		if (!r)
		{
			fp->count = -1;
			return ;
		}
		r_dup = r;
		if (fp->is_minus)
			memcpy(r_dup, *a, strlen(*a));
		else
			memcpy(r_dup + (fp->width - *a_len), *a, strlen(*a));
		r[fp->width] = '\0';
		free(*a);
		*a = r;
		*a_len = strlen(*a);
	}
}

void		format_u(struct fields *fp, unsigned int uval)
{
	char	*a;
	int		a_len;

	a_len = 0;
	get_a(fp, uval, &a, &a_len);
	if (fp->count == -1)
		return ;
	precision_u(fp, uval, &a, &a_len);
	if (fp->count == -1)
		return ;
	width_u(fp, &a, &a_len);
	if (fp->count == -1)
		return ;
	fp->count = fp->count + a_len;
	ft_putstr_fd(a, 1);
	free(a);
	return ;
}
