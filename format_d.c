/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 14:51:41 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/18 16:01:59 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		get_a(struct fields *fp, int dval, char **a, int *a_len)
{
	*a = ft_itoa(dval);
	if (!*a)
	{
		fp->count = -1;
		return ;
	}
	*a_len = strlen(*a);
}

void			helper_neg_d(char **a_dup, char **r_dup)
{
	**r_dup = '-';
	(*r_dup)++;
	(*a_dup)++;
}

void			precision_d(struct fields *fp, int dval, char **a, int *a_len)
{
	int		digits_a;
	char	*r;
	char	*r_dup;
	char	*a_dup;

	a_dup = *a;
	digits_a = count_digits(dval);
	if (fp->precision >= 0 && digits_a < fp->precision)
	{
		r = zalloc(fp->precision + *a_len + 1, sizeof(*r), '0');
		if (!r)
		{
			fp->count = -1;
			return ;
		}
		r_dup = r;
		if (dval < 0)
			helper_neg_d(&a_dup, &r_dup);
		strlcpy(r_dup + (fp->precision - digits_a), a_dup, strlen(r_dup) + 1);
		free(*a);
		*a = r;
	}
	else if (fp->precision == 0 && dval == 0)
		memset(*a, '\0', strlen(*a) + 1);
	*a_len = strlen(*a);
}

void			width_d(struct fields *fp, int dval, char **a, int *a_len)
{
	char *r;
	char *r_dup;
	char *a_dup;

	a_dup = *a;
	r = zalloc(fp->width + *a_len + 1, sizeof(*r), fp->padding_char);
	if (!r)
	{
		fp->count = -1;
		return ;
	}
	r_dup = r;
	if (fp->is_minus)
		memcpy(r_dup, *a, strlen(*a));
	else
	{
		if (dval < 0 && fp->padding_char == '0')
			helper_neg_d(&a_dup, &r_dup);
		memcpy(r_dup + (fp->width - *a_len), a_dup, strlen(*a));
	}
	r[fp->width] = '\0';
	free(*a);
	*a = r;
	*a_len = strlen(*a);
}

void			format_d(struct fields *fp, int dval)
{
	char			*a;
	int				a_len;

	a_len = 0;
	get_a(fp, dval, &a, &a_len);
	if (fp->count == -1)
		return ;
	precision_d(fp, dval, &a, &a_len);
	if (fp->count == -1)
		return ;
	if (a_len < fp->width)
		width_d(fp, dval, &a, &a_len);
	if (fp->count == -1)
		return ;
	fp->count = fp->count + a_len;
	ft_putstr_fd(a, 1);
	free(a);
	return ;
}
