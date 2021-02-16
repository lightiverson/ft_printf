/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_u.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:04:32 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/16 12:07:33 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_a(struct fields *fp, unsigned int uval, char **a, int *a_len)
{
	*a = ft_itoa(uval);
	if (!*a)
	{
		fp->count = -1;
		return ;
	}
	*a_len = strlen(*a);
}

void	precision_u(struct fields *fp, unsigned int uval, char *a, int *a_len)
{
	char r[fp->precision + *a_len + 1];
	char *p_r;

	p_r = r;
	if (fp->precision >= 0 && fp->precision > *a_len)
	{
		memset(r, '0', sizeof(r));
		memcpy(p_r + (fp->precision - *a_len), a, strlen(a));
		r[fp->precision] = '\0';
		free(a);
		a = ft_strdup(r);
		if (!a)
		{
			fp->count = -1;
			return ;
		}
		*a_len = strlen(a);
	}
	else if (fp->precision == 0 && uval == 0)
	{
		memset(a, '\0', strlen(a) + 1);
		*a_len = strlen(a);
	}
}

/*
void	width_u(struct fields *fp, char *a, int *a_len)
{
	char r[fp->width + *a_len + 1];
	char *p_r;

	p_r = r;
	if (fp->width > *a_len)
	{
		memset(p_r, fp->padding_char, sizeof(r));
		if (fp->is_minus)
			memcpy(p_r, a, strlen(a));
		else
			memcpy(p_r + (fp->width - *a_len), a, strlen(a));
		r[fp->width] = '\0';
		free(a);
		a = ft_strdup(r);
		if (!a)
		{
			fp->count = -1;
			return ;
		}
		*a_len = strlen(a);
	}
}
*/

void	*zalloc(size_t count, size_t size, struct fields *fp)
{
	void	*a;

	if ((count == 0) || (size == 0))
	{
		count = 1;
		size = 1;
	}
	a = malloc(count * size);
	if (a)
		ft_memset(a, fp->padding_char, count * size);
	return (a);
}

void	width_u(struct fields *fp, char **a, int *a_len)
{
	char *r;
	char *r_dup;

	if (fp->width > *a_len)
	{
		r = zalloc(fp->width + *a_len + 1, sizeof(char), fp);
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

void	format_u(struct fields *fp, unsigned int uval)
{
	char	*a;
	int		a_len;

	a_len = 0;
	get_a(fp, uval, &a, &a_len);
	if (fp->count == -1)
		return ;
	precision_u(fp, uval, a, &a_len);
	if (fp->count == -1)
		return ;
	width_u(fp, &a, &a_len);
	if (fp->count == -1)
		return ;
	fp->count = fp->count + strlen(a);
	ft_putstr_fd(a, 1);
	free(a);
	return ;
}
